


#ifndef INCLUDED_HOPPE_OPTIMIZER
#define INCLUDED_HOPPE_OPTIMIZER

#pragma once

#include <queue>
#include <list>
#include "../ProcessingLayer.h"


class HoppeOptimizer : public virtual ProcessingLayer
{
private:

	class Face
	{
	public:
		int id;
		int crossing;
		Face(int id = -1, int crossing = -1) : id(id), crossing(crossing) {}
		//Face() {}
	};


	enum Op { LOADED, UNLOADED };

	struct VertAction
	{
		Op op;
		int vert;
	};

	struct QAction
	{
		Op op;
		Face face;
	};

	struct ActionsTaken
	{
		ActionsTaken()
		{	}

		Face face_visited;
		std::list<VertAction> vertex_actions;
		std::list<QAction> q_actions;
		std::list<int> v_actions;
		std::list<int> f_actions;
		std::list<int> n_actions;
	};

	struct Strip
	{
		int from;
		int to;
	};


	struct FaceState
	{
		bool state[3];
	};


	struct TriNeighbors
	{
		bool visited;
		int num_neighbors;
		int neighbors[3];
		int start_vs[3];
		int visited_neighbors;
		std::vector<int> claimed_visit;

		TriNeighbors()
		{
			visited_neighbors = 0;
			visited = false;
			num_neighbors = 0;
			neighbors[0] = -1;
			neighbors[1] = -1;
			neighbors[2] = -1;
			start_vs[0] = -1;
			start_vs[1] = -1;
			start_vs[2] = -1;
		}

		void inc_neighbors()
		{
			num_neighbors++;
			if (num_neighbors > 3)
			{
				throw std::exception("Something went wrong!");
			}
		}

		void inc_visited(int who)
		{
			visited_neighbors++;
			claimed_visit.push_back(who);
			if (visited_neighbors > num_neighbors)
			{
				throw std::exception("Something went wrong!");
			}
		}

		void dec_visited()
		{
			visited_neighbors--;

			if (visited_neighbors < 0)
			{
				throw std::exception("Something went wrong!");
			}
		}
	};

	struct Neighbors
	{
		int a;
		int b;
		int temp;
	};

	Face s_u_f_w_f_u_n(std::vector<TriNeighbors>& neighbors);

	void next_unvisited_face(std::list<Face>& Q, Face& f, std::vector<TriNeighbors>& neighbors, ActionsTaken& current);

	void next_2_unvisited_faces(Face& fccw, Face& fclw, Face f, std::vector<TriNeighbors>& neighbors, ActionsTaken& current);

	int K;

	class Edge
	{
	private:
		int v_a;
		int v_b;

	public:

		bool operator<(const Edge b) const
		{
			uint64_t a64 = v_a;
			uint64_t b64 = v_b;
			uint64_t t = a64 | (b64 << 32);

			a64 = b.v_a;
			b64 = b.v_b;
			uint64_t o = a64 | (b64 << 32);

			return t < o;
		}

		Edge(int a, int b)
		{
			v_a = std::min(a, b);
			v_b = std::max(a, b);
		}

		int a() { return v_a; }

		int b() { return v_b; }
	};

	void mark_visited(const Face& f, std::vector<TriNeighbors>& visited_neighbors, ActionsTaken& current);

	bool strip_too_long(std::list<float>& visited_neighbors);

public:


	HoppeOptimizer(SceneSink& next, int cache_size);

	void process(const vertex* vertices, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices, const surface* surfaces, std::size_t num_surfaces, const material* materials, std::size_t num_materials, const texture* textures, std::size_t num_textures) override;
};

#endif  // INCLUDED_HOPPE_OPTIMIZER
