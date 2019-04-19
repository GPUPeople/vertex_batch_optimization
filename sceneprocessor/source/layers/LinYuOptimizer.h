


#ifndef INCLUDED_LINYU_OPTIMIZER
#define INCLUDED_LINYU_OPTIMIZER

#pragma once

#include <queue>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <list>
#include "../ProcessingLayer.h"
#include <boost/heap/fibonacci_heap.hpp>


class LinYuOptimizer : public virtual ProcessingLayer
{
private:

	enum Color {WHITE, GREY, BLACK};

	typedef std::unordered_map<int, Color> lymap;
	typedef std::unordered_set<int> lyset;

	int K;

	struct WhiteVert
	{
		int v;
		int valence;
	};

	struct compare_node
	{
		bool operator()(const WhiteVert& n1, const WhiteVert& n2) const
		{
			return n1.valence > n2.valence;
		}
	};

	typedef boost::heap::fibonacci_heap<WhiteVert, boost::heap::compare<compare_node>> white_queue;

	struct LYVertex
	{
		Color color;

		int white_count;

		int faces_count;

		lyset neighbors;

		std::vector<int> faces;

		LYVertex() : color(WHITE)
		{}
	};

	struct LYFace
	{
		bool output;

		int v[3];

		LYFace() : output(false)
		{}
	};

	void unregisterFace(std::vector<LYVertex>& lyvertices, const std::vector<LYFace>& lyfaces, int id, int except_id);

	int findBestCandidate(const std::list<int>& grey_vertices, white_queue& wh, std::vector<LYVertex>& lyvertices, const std::vector<LYFace>& lyfaces, std::vector<white_queue::handle_type>& i2h, std::set<int>& dirty_verts);

	//int findBestCandidate(const std::list<int>& grey_vertices, const lyset& white_vertices, std::vector<LYVertex>& lyvertices, const std::vector<LYFace>& lyfaces);

	void clearBlackPopable(std::list<int>& grey_vertices, std::vector<int>& black_vertices, const std::vector<LYVertex>& lyvertices);

	void simulate(int v_focus_ind, const std::vector<LYVertex>& lyvertices, const std::vector<LYFace>& lyfaces, std::list<int> grey_vertices, int &C1, int& C2, float& C3);

	void sortFacesClockwise(int v_id, LYVertex& v, const std::vector<LYFace>& lyfaces);

public:
	
	LinYuOptimizer(SceneSink& next, int cache_size);

	void process(const vertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, const surface* surfaces, std::size_t num_surfaces, const material* materials, std::size_t num_materials, const texture* textures, std::size_t num_textures) override;
};

#endif  // INCLUDED_HOPPE_OPTIMIZER
