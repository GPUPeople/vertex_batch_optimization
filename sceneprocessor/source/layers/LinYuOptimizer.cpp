
#include <map>

#include <iostream>

#include "LinYuOptimizer.h"
#include <list>


#define SHOW_REORDERED_FACES false
#define SHOW_PROGRESS false

LinYuOptimizer::LinYuOptimizer(SceneSink& next, int cache_size)
	: ProcessingLayer(next), K(cache_size)
{
}


void LinYuOptimizer::simulate(int v_focus_ind, const std::vector<LYVertex>& lyvertices, const std::vector<LYFace>& lyfaces, std::list<int> grey_vertices, int &C1, int& C2, float& C3)
{
	C1 = 0, C2 = 0;

	const LYVertex& v_focus = lyvertices[v_focus_ind];

	lymap vertex_delta;

	for (auto f_ind : v_focus.faces)
	{
		const LYFace& f = lyfaces[f_ind];

		if (f.output)
		{
			continue;
		}

		C2++;

		for (auto v_ind : f.v)
		{
			Color col = (vertex_delta.find(v_ind) != vertex_delta.end() ? vertex_delta[v_ind] : lyvertices[v_ind].color);

			if (col != WHITE)
			{
				continue;
			}

			//POP
			if (grey_vertices.size() == K)
			{
				int w_ind = grey_vertices.back();
				grey_vertices.pop_back();
				vertex_delta[w_ind] = WHITE;
			}

			//PUSH
			C1++;

			grey_vertices.push_front(v_ind);
			vertex_delta[v_ind] = GREY;
		}
	}

	Color final_color = (vertex_delta.find(v_focus_ind) == vertex_delta.end() ? v_focus.color : vertex_delta[v_focus_ind]);

	if (final_color == WHITE)
	{
		C3 = 1.0f;
	}
	else
	{
		auto it = grey_vertices.begin();
		int pos;

		for (pos = 0; pos < grey_vertices.size(); pos++)
		{
			if (*it == v_focus_ind)
			{
				break;
			}
			it = std::next(it);
		}

		C3 = (K - pos) / ((float)K);
	}
}

void LinYuOptimizer::clearBlackPopable(std::list<int>& grey_vertices, std::vector<int>& black_vertices, const std::vector<LYVertex>& lyvertices)
{
	while (grey_vertices.size() && lyvertices[grey_vertices.back()].color == BLACK)
	{
		int v_id = grey_vertices.back();

		black_vertices.push_back(v_id);

		grey_vertices.pop_back();
	}
}

int LinYuOptimizer::findBestCandidate(const std::list<int>& grey_vertices, white_queue& wh, std::vector<LYVertex>& lyvertices, const std::vector<LYFace>& lyfaces, std::vector<white_queue::handle_type>& i2h, std::set<int>& dirty_verts)
{
	float min_val = FLT_MAX;
	int min_ind = -1;

	if (grey_vertices.size() == 0)
	{
		for (int v : dirty_verts)
		{
			for (int n : lyvertices[v].neighbors)
			{
				if (lyvertices[n].color == WHITE)
				{
					int count = 0;
					for (int c : lyvertices[n].neighbors)
					{
						if (lyvertices[c].color == WHITE)
						{
							count++;
						}
					}
					lyvertices[n].white_count = count;
					wh.update(i2h[n], { n, count });
				}
			}
		}
		dirty_verts.clear();

		WhiteVert wv = wh.top();
		return wv.v;
		//find white vertex with minimum degree
		//for (auto v_ind : white_vertices)
		//{
		//	//return wv.v;

		//	float count = (float)lyvertices[v_ind].white_count;
		//	if (count < min_val)
		//	{
		//		min_val = count;
		//		min_ind = v_ind;

		//		if (count == 0)
		//		{
		//			break;
		//		}
		//	}
		//}
	}
	else
	{
		//find grey vertex in cache with best score
		for (auto v_ind : grey_vertices)
		{
			if (lyvertices[v_ind].color == BLACK) // it is actually black (should be popped soon)
			{
				continue;
			}

			int C1, C2;
			float C3;
			simulate(v_ind, lyvertices, lyfaces, grey_vertices, C1, C2, C3);

			float cost = 1.0f * C1 - 0.5f * C2 + 1.3f * C3;
			if (cost < min_val)
			{
				min_val = cost;
				min_ind = v_ind;
			}
		}
	}

	return min_ind;
}

void LinYuOptimizer::unregisterFace(std::vector<LYVertex>& lyvertices, const std::vector<LYFace>& lyfaces, int id, int except_id = INT_MAX)
{
	const LYFace& output_face = lyfaces[id];
	for (auto bound_ind : output_face.v)
	{
		if (bound_ind == except_id)
		{
			continue;
		}

		if (--lyvertices[bound_ind].faces_count == 0)
		{
			lyvertices[bound_ind].color = BLACK;
		}
	}
}

void LinYuOptimizer::sortFacesClockwise(int v_id, LYVertex& v, const std::vector<LYFace>& lyfaces)
{
	std::vector<int> sorted_faces;
	std::vector<bool> assigned(v.faces.size(), false);

	int start_id = 0;

	while (sorted_faces.size() != v.faces.size())
	{
		//find lowest non-assigned face as start

		for (; start_id < assigned.size(); start_id++)
		{
			if (!assigned[start_id])
			{
				assigned[start_id] = true;
				break;
			}
		}

		sorted_faces.push_back(v.faces[start_id]);

		if (sorted_faces.size() < v.faces.size())
		{
			const LYFace* curr_face = &lyfaces[v.faces[start_id]];

			bool success = true;

			while (success)
			{
				int base1;
				for (base1 = 0; base1 < 3; base1++)
				{
					if (curr_face->v[base1] == v_id)
					{
						break;
					}
				}
				int base2 = (base1 + 1) % 3;
				int w_id = curr_face->v[base2];

				int t_id;
				for (t_id = 0; t_id < v.faces.size(); t_id++)
				{
					if (assigned[t_id])
					{
						continue;
					}

					const LYFace& t = lyfaces[v.faces[t_id]];

					if (t.v[0] == w_id || t.v[1] == w_id || t.v[2] == w_id)
					{
						break;
					}
				}

				if (t_id == v.faces.size())
				{
					success = false;
				}
				else
				{
					curr_face = &lyfaces[v.faces[t_id]];
					assigned[t_id] = true;

					sorted_faces.push_back(v.faces[t_id]);
				}
			}
		}
	}

#if SHOW_REORDERED_FACES
	for (int i = 0; i < sorted_faces.size(); i++)
	{
		std::cout << lyfaces[sorted_faces[i]].v[0] << " " << lyfaces[sorted_faces[i]].v[1] << " " << lyfaces[sorted_faces[i]].v[2] << std::endl;
	}
#endif

	v.faces = sorted_faces;
}

void LinYuOptimizer::process(const vertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, const surface* surfaces, std::size_t num_surfaces, const material* materials, std::size_t num_materials, const texture* textures, std::size_t num_textures)
{
	std::cout << "------------------ Lin-Yu optimizer (" << K << ") ------------------\n";

	std::vector<uint32_t> new_indices(num_indices);

	for (auto surface = surfaces; surface < surfaces + num_surfaces; ++surface)
	{
		std::vector<LYVertex> lyvertices(num_vertices);
		std::set<int> dirty_verts;
		std::vector<LYFace> lyfaces;

		if (surface->primitive_type != PrimitiveType::TRIANGLES)
		{
			throw std::exception("Unsupported shape!");
		}

		std::cout << "Pre-conversion..." << std::endl;

		lyset white_vertices;
		for (auto start = surface->start; start < (surface->start + surface->num_indices); start += 3)
		{
			lyfaces.push_back(LYFace());
			for (int i = 0; i < 3; i++)
			{
				int s = indices[start + i];
				int t = indices[start + ((i + 1) % 3)];

				white_vertices.insert(s);

				lyfaces.back().v[i] = s;

				lyvertices[s].faces.push_back((int)lyfaces.size() - 1);
				lyvertices[s].neighbors.insert(t);
				lyvertices[t].neighbors.insert(s);
			}
		}

		std::cout << "Sorting..." << std::endl;

		for (int v_pos = 0; v_pos < lyvertices.size(); v_pos++)
		{
			LYVertex& vertex = lyvertices[v_pos];
			sortFacesClockwise(v_pos, vertex, lyfaces);
			vertex.faces_count = (int)vertex.faces.size();
			vertex.white_count = (int)vertex.neighbors.size();
		}

		white_queue bh;

		std::vector<white_queue::handle_type> ind2handle(num_vertices);

		for (auto s : white_vertices)
		{
			WhiteVert v = { s, lyvertices[s].white_count };
			ind2handle[s] = bh.push(v);
		}

		std::list<int> grey_vertices;
		std::vector<int> black_vertices;
		std::vector<int> output_f_ordered;

		int output = 0;
		int num_verts = (int)white_vertices.size();

		std::cout << "Rearranging..." << std::endl;

		while (black_vertices.size() != num_verts)
		{
			int v_focus_ind = findBestCandidate(grey_vertices, bh, lyvertices, lyfaces, ind2handle, dirty_verts);

			if (v_focus_ind == -1)
			{
				throw std::exception("No candidate vertex found, hell broke loose! Check code carefully!");
			}

			LYVertex& v_focus = lyvertices[v_focus_ind];

			for (auto f_ind : v_focus.faces)
			{
				LYFace& f = lyfaces[f_ind];

				if (f.output)
				{
					continue;
				}

				for (auto v_ind : f.v)
				{
					LYVertex& v = lyvertices[v_ind];

					if (v.color != WHITE) //already in cache
					{
						continue;
					}

					if (grey_vertices.size() == K)
					{
						int w_ind = grey_vertices.back();
						grey_vertices.pop_back();

						LYVertex& w = lyvertices[w_ind];
						if (w.color == BLACK)
						{
							black_vertices.push_back(w_ind);
						}
						else
						{
							w.color = WHITE;
							ind2handle[w_ind] = bh.push({ w_ind, 0 });
							//white_vertices.insert(w_ind);
						}
						dirty_verts.insert(w_ind);
					}
					dirty_verts.insert(v_ind);

					v.color = GREY;
					grey_vertices.push_front(v_ind);
					bh.erase(ind2handle[v_ind]);
					//white_vertices.erase(v_ind);

					std::vector<int> faces_to_output;

					for (auto f_cand_ind : v.faces)
					{
						if (f_cand_ind == f_ind) //not the current focus face
						{
							continue;
						}

						LYFace& cand_face = lyfaces[f_cand_ind];

						if (cand_face.output) //face already rendered.
						{
							continue;
						}

						LYVertex &a = lyvertices[cand_face.v[0]], &b = lyvertices[cand_face.v[1]], &c = lyvertices[cand_face.v[2]];

						if (a.color == GREY && b.color == GREY && c.color == GREY)
						{
							cand_face.output = true;
							output_f_ordered.push_back(f_cand_ind);
							unregisterFace(lyvertices, lyfaces, f_cand_ind, v_focus_ind);
							output++;
						}
					}
				}
				if (!f.output)
				{
					dirty_verts.insert(f.v[0]);
					dirty_verts.insert(f.v[1]);
					dirty_verts.insert(f.v[2]);

					f.output = true;
					output_f_ordered.push_back(f_ind);
					unregisterFace(lyvertices, lyfaces, f_ind, v_focus_ind);
					output++;
				}
				else
				{
					throw std::exception("Focus face was already rendered earlier. Please debug, this shouldn't happen.");
				}
			}

			dirty_verts.insert(v_focus_ind);

			if (v_focus.color != GREY) //just in case it was left out --> direct transition or swapped out
			{
				bh.erase(ind2handle[v_focus_ind]);
				black_vertices.push_back(v_focus_ind);
				//white_vertices.erase(v_focus_ind);
			}

			v_focus.faces_count = 0;
			v_focus.color = BLACK; //if in cache, wait for pop operations to remove it

#if SHOW_PROGRESS
			static int last_check = 0;
			if (output >= last_check + 10000)
			{
				std::cout << output << "/" << surface->num_indices / 3 << std::endl;
				last_check = output;
			}
#endif

			//clear out all popable black vertices
			clearBlackPopable(grey_vertices, black_vertices, lyvertices);
		}

		if (output_f_ordered.size() * 3 != surface->num_indices)
		{
			throw std::exception("What the hell happened!");
		}

		for (int done = 0; done < num_indices / 3; done++)
		{
			int face_ind = output_f_ordered[done];
			LYFace& f = lyfaces[face_ind];

			new_indices[surface->start + done * 3 + 0] = f.v[0];
			new_indices[surface->start + done * 3 + 1] = f.v[1];
			new_indices[surface->start + done * 3 + 2] = f.v[2];
		}
	}

	ProcessingLayer::process(vertices, num_vertices, &new_indices[0], new_indices.size(), surfaces, num_surfaces, materials, num_materials, textures, num_textures);
}