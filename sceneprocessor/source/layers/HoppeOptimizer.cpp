
#include <map>

#include <iostream>

#include "HoppeOptimizer.h"
#include <set>
#include <list>
#include <DirectXMesh/DirectXMesh.h>

#define SIM_LENGTH 5//(K+5)

HoppeOptimizer::HoppeOptimizer(SceneSink& next, int cache_size)
	: ProcessingLayer(next), K(cache_size)
{
}

void HoppeOptimizer::next_unvisited_face(std::list<Face>& Q, Face& f, std::vector<TriNeighbors>& neighbors, ActionsTaken& current)
{
	f = Face(-1, -1);

	while (!Q.empty())
	{
		Face t = Q.front();
		Q.pop_front();

		//Allow undoing it
		current.q_actions.push_back({ UNLOADED, t });

		if (t.id != -1 && neighbors[t.id].visited == false)
		{
			f = t;
			break;
		}
	}
}

void HoppeOptimizer::next_2_unvisited_faces(Face& fccw, Face& fclw, Face f, std::vector<TriNeighbors>& neighbors, ActionsTaken& current)
{
	TriNeighbors& orig = neighbors[f.id];

	if (f.crossing == -1)
	{
		for (int i = 0; i < 3; i++)
		{
			if (orig.neighbors[i] == -1 || neighbors[orig.neighbors[i]].visited == true)
			{
				f.crossing = i;

				//Allow undoing it
				current.f_actions.push_back(-1);

				break;
			}
		}
	}

	{
		int cl_i = (f.crossing + 1) % 3;
		if (orig.neighbors[cl_i] != -1 && neighbors[orig.neighbors[cl_i]].visited == false)
		{
			fclw = Face(orig.neighbors[cl_i], orig.start_vs[cl_i]);
		}
	}

	{
		int cw_i = (f.crossing + 2) % 3;
		if (orig.neighbors[cw_i] != -1 && neighbors[orig.neighbors[cw_i]].visited == false)
		{
			fccw = Face(orig.neighbors[cw_i], orig.start_vs[cw_i]);
		}
	}
}

HoppeOptimizer::Face HoppeOptimizer::s_u_f_w_f_u_n(std::vector<TriNeighbors>& neighbors)
{
	int min_v = INT_MAX;
	int min_v_id = -1;
	int min_f = INT_MAX;
	int min_f_id = -1;

	for (int i = 0; i < neighbors.size(); i++)
	{
		if (!neighbors[i].visited)
		{
			if (neighbors[i].visited_neighbors < min_v)
			{
				min_v = neighbors[i].visited_neighbors;
				min_v_id = i;
			}

			if (neighbors[i].num_neighbors < min_f)
			{
				min_f = neighbors[i].num_neighbors;
				min_f_id = i;
			}
		}
	}

	if (min_v == 0) // Start!
	{
		return { min_f_id, -1 };
	}
	else
	{
		return { min_v_id, -1 };
	}
}

void HoppeOptimizer::mark_visited(const Face& f, std::vector<TriNeighbors>& visited_neighbors, ActionsTaken& current)
{
	if (!visited_neighbors[f.id].visited)
	{
		visited_neighbors[f.id].visited = true;
		//Allow undoing it
		current.n_actions.push_back(f.id);
	}

	for (int i = 0; i < 3; i++)
	{
		if (visited_neighbors[f.id].neighbors[i] != -1)
		{
			int id = visited_neighbors[f.id].neighbors[i];

			visited_neighbors[id].inc_visited(f.id);
			//Allow undoing it
			current.v_actions.push_back(id);
		}
	}
}

bool HoppeOptimizer::strip_too_long(std::list<float>& acmr)
{
	if (acmr.size() <= SIM_LENGTH)
	{
		return false;
	}

	int min_id;
	float minimum = FLT_MAX;

	auto it = acmr.rbegin();
	for (int i = SIM_LENGTH - 1; i >= 0; i--)
	{
		if (*it < minimum)
		{
			minimum = *it;
			min_id = i;
		}
		it++;
	}

	if (min_id == 0)		//smallest ACMR was found (K+5) entries ago
	{
		return true;
	}

	return false;
}

void HoppeOptimizer::process(const vertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, const surface* surfaces, std::size_t num_surfaces, const material* materials, std::size_t num_materials, const texture* textures, std::size_t num_textures)
{
	std::cout << "------------------ hoppe optimizer ------------------\n";

	std::vector<std::uint32_t> new_indices(indices, indices + num_indices);

	std::vector<DirectX::XMFLOAT3> pos(num_vertices);
	for (std::size_t j = 0; j < num_vertices; ++j)
	{
		pos[j] = DirectX::XMFLOAT3(vertices[j].p.x, vertices[j].p.y, vertices[j].p.z);
	}

	for (auto surface = surfaces; surface < surfaces + num_surfaces; ++surface)
	{
		std::map<Edge, Neighbors> edges;

		if (surface->primitive_type != PrimitiveType::TRIANGLES)
		{
			throw std::exception("Unsupported shape!");
		}

		const uint32_t* surface_indices = indices + surface->start;
		uint32_t num_faces = surface->num_indices / 3;

		std::vector<uint32_t> adj(surface->num_indices);
		if (FAILED(DirectX::GenerateAdjacencyAndPointReps(surface_indices, num_faces, pos.data(), num_vertices, 0.f, nullptr, adj.data())))
			throw std::exception("Couldnt generate adjacency");
			// Error

		std::vector<uint32_t> faceRemap(num_faces);
		if (FAILED(DirectX::OptimizeFaces(surface_indices, num_faces, adj.data(), faceRemap.data())))
			throw std::exception("Couldnt optimize faces");
		//	// Error

		std::vector<uint32_t> newIndices(surface->num_indices);
		if (FAILED(DirectX::ReorderIB(surface_indices, num_faces, faceRemap.data(), new_indices.data() + surface->start)))
			throw std::exception("Couldnt reorder");

		//std::vector<TriNeighbors> visited_neighbors(surface->num_indices / 3);

		//for (auto start = surface->start; start < (surface->start + surface->num_indices); start += 3)
		//{
		//	for (int i = 0; i < 3; i++)
		//	{
		//		int s = start + i;
		//		int t = start + ((i + 1) % 3);

		//		Edge e(indices[s], indices[t]);

		//		if (edges.find(e) != edges.end())
		//		{
		//			if (edges[e].a != -1 && edges[e].b == -1)
		//			{
		//				edges[e].b = start / 3;

		//				{
		//					TriNeighbors& neighbors_a = visited_neighbors[edges[e].a];
		//					neighbors_a.neighbors[edges[e].temp] = edges[e].b;
		//					neighbors_a.start_vs[edges[e].temp] = i;
		//					neighbors_a.inc_neighbors();
		//				}

		//				{
		//					TriNeighbors& neighbors_b = visited_neighbors[edges[e].b];
		//					neighbors_b.neighbors[i] = edges[e].a;
		//					neighbors_b.start_vs[i] = edges[e].temp;
		//					neighbors_b.inc_neighbors();
		//				}
		//			}
		//			else // edge overflow, happens with non-2-manifold
		//			{
		//				edges.erase(e);
		//			}
		//		}

		//		if (edges.find(e) == edges.end())
		//		{
		//			edges[e].a = start / 3;
		//			edges[e].b = -1;
		//			edges[e].temp = i;
		//		}
		//	}
		//}

		//Face f;
		//std::list<int> F;
		//std::vector<Strip> strips;

		//std::set<int> cache_set;
		//std::list<int> cache_list;

		//std::list<ActionsTaken> history;

		//while (true)
		//{
		//	if (strips.size())
		//	{
		//		strips.back().to = static_cast<int>(F.size());
		//	}

		//	strips.push_back({ (int)F.size(), -1 });

		//	if (f.id == -1)
		//	{
		//		f = s_u_f_w_f_u_n(visited_neighbors);
		//		if (f.id == -1)
		//		{	break;	}
		//	}

		//	std::list<Face> Q;
		//	std::list<float> acmr_list;

		//	while (true)
		//	{
		//		//if(false)
		//		if(strip_too_long(acmr_list)) //Best acmr was SIM_LENGTH faces ago!
		//		{
		//			//restore cache and state
		//			for (int t = 0; t < SIM_LENGTH; t++)
		//			{
		//				ActionsTaken& tk = history.back();

		//				f = tk.face_visited;

		//				for (auto it = tk.vertex_actions.rbegin(); it != tk.vertex_actions.rend(); it++)
		//				{
		//					if (it->op == LOADED)
		//					{
		//						cache_set.erase(cache_list.back());
		//						cache_list.pop_back();
		//					}
		//					else
		//					{
		//						cache_set.insert(it->vert);
		//						cache_list.push_front(it->vert);
		//					}
		//				}
		//				for (auto it = tk.q_actions.rbegin(); it != tk.q_actions.rend(); it++)
		//				{
		//					if (it->op == LOADED)
		//					{	Q.pop_back();	}
		//					else
		//					{	Q.push_front(it->face);	}
		//				}
		//				for (auto it = tk.f_actions.begin(); it != tk.f_actions.end(); it++)
		//				{	f.crossing = -1;	}
		//				for (auto it = tk.v_actions.begin(); it != tk.v_actions.end(); it++)
		//				{	visited_neighbors[*it].dec_visited();	}
		//				for (auto it = tk.n_actions.begin(); it != tk.n_actions.end(); it++)
		//				{	visited_neighbors[f.id].visited = false;	}

		//				F.pop_back();
		//				history.pop_back();
		//				acmr_list.pop_back();
		//			}

		//			break;
		//		}

		//		ActionsTaken current;

		//		mark_visited(f, visited_neighbors, current);

		//		//Adding f to F, simulating cache
		//		{
		//			F.push_back(f.id);

		//			int base = F.back() * 3;
		//			unsigned int abc[3] = { indices[base], indices[base + 1], indices[base + 2] };

		//			float misses = 0;
		//			for (int i = 0; i < 3; i++)
		//			{
		//				if (cache_set.find(abc[i]) == cache_set.end())
		//				{
		//					misses++;

		//					if (cache_list.size() >= K)
		//					{
		//						int kill = cache_list.front();
		//						cache_list.pop_front();
		//						cache_set.erase(kill);

		//						current.vertex_actions.push_back({ UNLOADED, kill });
		//					}

		//					cache_set.insert(abc[i]);
		//					cache_list.push_back(abc[i]);

		//					current.vertex_actions.push_back({ LOADED, (int)abc[i] });
		//				}
		//			}
		//			float Z = acmr_list.size() ? acmr_list.back() : 0;

		//			acmr_list.push_back(Z + (misses - Z) / (acmr_list.size() + 1));
		//		}

		//		Face fccw, fclw;
		//		next_2_unvisited_faces(fccw, fclw, f, visited_neighbors, current);

		//		current.face_visited = f;

		//		history.push_back(current);

		//		if (fccw.id != -1)
		//		{
		//			Q.push_back(fclw);

		//			history.back().q_actions.push_back({ LOADED , fclw.id });

		//			f = fccw;
		//		}
		//		else if (fclw.id != -1)
		//		{
		//			f = fclw;
		//		}
		//		else
		//		{
		//			next_unvisited_face(Q, f, visited_neighbors, current);
		//			break;
		//		}
		//	}
		//}

		//if (strips.size())
		//{
		//	strips.back().to = static_cast<int>(F.size());
		//}

		//if (F.size() != visited_neighbors.size())
		//{
		//	throw std::exception("Something went wrong!");
		//}

		//int i = 0;
		//for (auto it = F.begin(); it != F.end(); it++)
		//{
		//	for (int j = 0; j < 3; j++)
		//	{
		//		new_indices[i + j] = indices[*it * 3 + j];
		//	}
		//	i += 3;
		//}
	}

	ProcessingLayer::process(vertices, num_vertices, &new_indices[0], new_indices.size(), surfaces, num_surfaces, materials, num_materials, textures, num_textures);
}
