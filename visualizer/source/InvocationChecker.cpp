


#include <memory>
#include <random>
#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <functional>

#include <core/utils/memory>
#include <core/utils/io>

#include <GL/error.h>

#include "InvocationChecker.h"


extern const char invocation_counter_vs[];
extern const char invocation_counter_gs[];
extern const char invocation_counter_fs[];

namespace
{
	auto generateColors(int num_colors)
	{
		auto color_buffer = core::make_unique_default<std::uint32_t[]>(num_colors);

		std::generate(&color_buffer[0], &color_buffer[0] + num_colors, [i = 0, color = 0U, rnd = std::mt19937(42), dist = std::uniform_int_distribution<unsigned int>(0, 0xFFFFFF)]() mutable
		{
			color = dist(rnd);
			return 0xFF000000U | color;
		});

		return color_buffer;
	}

	void compareReuse(std::uint32_t* sim_inv, const std::uint32_t* inv_counters, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices)
	{
		size_t batchsize = 96;

		std::fill(sim_inv, sim_inv + num_vertices, 0);
		size_t cbatch = 0;
		std::unordered_set<std::uint32_t> batchv;
		for (size_t i = 0; i < num_indices; ++i, ++cbatch)
		{
			if (cbatch == batchsize)
			{
				batchv.clear();
				cbatch = 0;
			}
			std::uint32_t id = indices[i];
			if (batchv.find(id) == end(batchv))
			{
				batchv.insert(id);
				++sim_inv[id];
			}
		}

		size_t sim_inv_counter = 0, real_inv = 0;
		std::cout << "real inv vs simulated:\n";
		for (size_t i = 0; i < num_vertices; ++i)
		{
			if (sim_inv[i] != inv_counters[i])
				std::cout << i << ": " << inv_counters[i] << " " << sim_inv[i] << "\n";
			sim_inv_counter += sim_inv[i];
			real_inv += inv_counters[i];
		}
		std::cout << "real rate: " << 3 * static_cast<double>(real_inv) / num_indices << "\n";
		std::cout << "sim rate: " << 3 * static_cast<double>(sim_inv_counter) / num_indices << "\n";
	}
}

InvocationChecker::InvocationChecker(Display& display, const GeometryVertex* vertices, std::size_t num_vertices, const std::uint32_t* _indices, std::size_t num_indices)
	: display(display),
	num_vertices(static_cast<GLsizei>(num_vertices)),
	num_indices(static_cast<GLsizei>(num_indices)),
	indices(_indices, _indices + num_indices)
{
	if (GLint64 max_texture_buffer_size; glGetInteger64v(GL_MAX_TEXTURE_BUFFER_SIZE, &max_texture_buffer_size), max_texture_buffer_size < static_cast<GLint64>(num_vertices))
		std::cerr << "WARNING: GL_MAX_TEXTURE_BUFFER_SIZE less than num_vertices\n";

	{
		auto vs = GL::compileVertexShader(invocation_counter_vs);
		auto gs = GL::compileGeometryShader(invocation_counter_gs);
		auto fs = GL::compileFragmentShader(invocation_counter_fs);

		glAttachShader(prog_invo, vs);
		glAttachShader(prog_invo, gs);
		glAttachShader(prog_invo, fs);
		GL::linkProgram(prog_invo);
	}

	glBindVertexArray(vao);
	glUseProgram(prog_invo);
	GL::throw_error();
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferStorage(GL_ARRAY_BUFFER, static_cast<GLsizei>(num_vertices * sizeof(GeometryVertex)), vertices, 0U);
	GL::throw_error();

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, vertex_invocation_counter_buffer);
	glBufferStorage(GL_SHADER_STORAGE_BUFFER, num_vertices * 4U, nullptr, GL_DYNAMIC_STORAGE_BIT);
	int zero = 0;
	glClearBufferData(GL_SHADER_STORAGE_BUFFER, GL_R32UI, GL_RED, GL_UNSIGNED_INT, &zero);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, vertex_invocation_counter_buffer);

	//std::vector<uint32_t> valences(num_vertices, 0);
	//for (size_t i = 0; i < num_indices; ++i)
	//	++valences[indices[i]];
	//maxvalence = 0;
	//for (auto v : valences)
	//	maxvalence = std::max(maxvalence, v);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, vertex_invocation_timing_buffer);
	glBufferStorage(GL_SHADER_STORAGE_BUFFER, num_indices / 3 * 4U * 4U, nullptr, GL_DYNAMIC_STORAGE_BIT);
	//int zero4[] = { 0,0,0,0 };
	//glClearBufferData(GL_SHADER_STORAGE_BUFFER, GL_RGBA32UI, GL_RGBA, GL_UNSIGNED_INT, zero4);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, vertex_invocation_timing_buffer);


	GL::throw_error();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
	glBufferStorage(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizei>(num_indices * 4U), _indices, GL_DYNAMIC_STORAGE_BIT);// 0U);

	
	glBindVertexBuffer(0U, vertex_buffer, 0U, sizeof(GeometryVertex));

	glEnableVertexAttribArray(0U);
	glEnableVertexAttribArray(1U);
	glVertexAttribFormat(0U, 3, GL_FLOAT, GL_FALSE, 0U);
	glVertexAttribFormat(1U, 3, GL_FLOAT, GL_FALSE, 12U);

	glVertexAttribBinding(0U, 0U);
	glVertexAttribBinding(1U, 0U);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
	GL::throw_error();

	{
		int num_primitives = static_cast<int>(num_indices / 3);
		auto batch_colors = generateColors(32*1024);
		glBindBuffer(GL_TEXTURE_BUFFER, color_buffer);
		glBufferStorage(GL_TEXTURE_BUFFER, 32 * 1024 * 4U, &batch_colors[0], 0U);

		glBindTexture(GL_TEXTURE_BUFFER, color_buffer_texture);
		glTextureBuffer(color_buffer_texture, GL_RGBA8, color_buffer);
	}

	GL::throw_error();
}


void InvocationChecker::runCheck() const
{


}

size_t simulateReuse(std::uint32_t* sim_inv, const std::uint32_t* inv_counters, std::size_t num_vertices, 
	const std::uint32_t* indices, std::size_t num_indices)//, const uint32_t* batchIds)
{
	size_t batchsize = 96;
	size_t lookahead = 42;
	size_t warpsize = 32;

	if(inv_counters != nullptr)
		std::fill(sim_inv, sim_inv + num_vertices, 0);
	size_t cbatch = 0;
	size_t uniques = 0;
	size_t overallInvocations = 0;
	std::unordered_set<std::uint32_t> batchv;
	//std::vector<std::uint32_t> lookahead_end(batchsize > lookahead ? batchsize - lookahead + 1: 1, 0xFFFFFFFF);
	std::vector<std::uint32_t> keepalive(batchsize, 0xFFFFFFFF);

	//std::cout << "\n" << num_indices << "\n";
	std::vector<uint32_t> lasts(3, 0xFFFFFFFF);
	std::vector < std::tuple<size_t,uint32_t, size_t, size_t>> boundadries;
	uint32_t lastBatchId = 0;
	for (size_t i = 0; i < num_indices; )
	{
		/*if (cbatch >= lookahead)
		{
			uint32_t v = lookahead_end[cbatch - lookahead];
			if (v != 0xFFFFFFFF)
				batchv.erase(v);
		}*/



		std::uint32_t id = indices[i];
		lasts[0] = lasts[1];
		lasts[1] = lasts[2];
		lasts[2] = 0xFFFFFFFF;

		if (batchv.find(id) == end(batchv))
		{

			batchv.insert(id);
			//std::cout << id << "\n";
			++sim_inv[id];
			//std::cout << id << "\n";
			lasts[2] = id;
			++uniques;
			++overallInvocations;
		}

		for (size_t j = cbatch; j < std::min(batchsize, cbatch + lookahead); ++j)
		{
			if (keepalive[j] == id)
				keepalive[j] = 0xFFFFFFFF;
		}
		if (cbatch + lookahead < batchsize)
			keepalive[cbatch + lookahead] = id;

		//The magic point where the reuse "keepalive changes to infinity...?"
		if (keepalive[cbatch] != 0xFFFFFFFF)// && uniques < warpsize-1)
			batchv.erase(keepalive[cbatch]);

		++i;
		++cbatch;
		if (uniques > warpsize)
		{
			//std::fill(begin(lookahead_end), end(lookahead_end), 0xFFFFFFFF);
			std::fill(begin(keepalive), end(keepalive), 0xFFFFFFFF);
			batchv.clear();

			size_t putback = 1 + ((i - 1) % 3);
			i = i - putback;

			boundadries.push_back(std::make_tuple(i, 1, cbatch - putback, putback));
			cbatch = 0;
			uniques = 0;

			for (size_t j = 3 - putback; j < 3; ++j)
			{
				if (lasts[j] != 0xFFFFFFFF)
				{
					--sim_inv[lasts[j]];
					--overallInvocations;
				}
			}
		} 
		else if (cbatch == batchsize)
		{
			//std::fill(begin(lookahead_end), end(lookahead_end), 0xFFFFFFFF);
			std::fill(begin(keepalive), end(keepalive), 0xFFFFFFFF);
			batchv.clear();
			cbatch = 0;
			boundadries.push_back(std::make_tuple(i, 0, uniques, batchsize));
			uniques = 0;
		}

		//uint32_t primitive = static_cast<uint32_t>(i) / 3;
		//bool primitiveBoundary = (i % 3) == 0;
		//if (primitiveBoundary)
		//{
		//	uint32_t nbatch = batchIds[primitive];
		//	bool simbound = cbatch;
		//	bool realbound = nbatch != lastBatchId;

		//	if (simbound != realbound)
		//	{
		//		std::cout << "different bounds at batch:\n";
		//		//TODO: output batch
		//	}
		//	if (realbound)
		//	{
		//		std::fill(begin(keepalive), end(keepalive), 0xFFFFFFFF);
		//		batchv.clear();
		//		cbatch = 0;
		//		boundadries.push_back(std::make_tuple(i, 0, uniques, batchsize));
		//		uniques = 0;
		//	}
		//}

		/*else if (i % 382215 == 0)
		{
			std::fill(begin(keepalive), end(keepalive), 0xFFFFFFFF);
			batchv.clear();
			boundadries.push_back(std::make_tuple(i, 3, uniques, cbatch));
			cbatch = 0;
			uniques = 0;
		}*/
		/*else if (cbatch % 3 == 0 &&
			(indices[i-1] == indices[i-2] || indices[i-2] == indices[i - 3] || indices[i-1] == indices[i - 3])
			)
		{
			std::cout << "deg; " << i << std::endl;
			std::fill(begin(keepalive), end(keepalive), 0xFFFFFFFF);
			batchv.clear();
			boundadries.push_back(std::make_tuple(i, 0, uniques, batchsize));
			cbatch = 0;
			uniques = 0;
		}*/
	}
	boundadries.push_back(std::make_tuple(num_indices+1, 0, uniques, cbatch));

	
	if(inv_counters != nullptr)
	{ 
		size_t sim_inv_counter = 0, real_inv = 0;
		bool same = true;

		for (size_t i = 0; i < num_vertices; ++i)
		{
			//if (sim_inv[i] + inv_counters[i] != 0)
			if (sim_inv[i] != inv_counters[i])
			{
				if (same)
					std::cout << "real inv vs simulated:\n";
				same = false;
				if(false)
				std::cout << i << ": " << inv_counters[i] << " " << sim_inv[i] << "\n";
			}
			sim_inv_counter += sim_inv[i];
			real_inv += inv_counters[i];
		}
		std::cout << "real rate: " << 3 * static_cast<double>(real_inv) / num_indices << "\n";
		std::cout << "sim rate: " << 3 * static_cast<double>(sim_inv_counter) / num_indices << "\n";

		if (false && !same)
		{
			const char* bs = "----------------";
			std::cout << bs << "\n";
			auto nb = begin(boundadries);
			for (size_t i = 0; i < num_indices; ++i)
			{
				if (std::get<0>(*nb) == i)
				{
					std::cout << bs;
					if(std::get<1>(*nb) != 1)
						std::cout << " <"<< std::get<3>(*nb) << "," << std::get<2>(*nb) << ">";
					else
						std::cout << " <"<< std::get<2>(*nb) << ",32/-" <<  (std::get<3>(*nb)-1) << ">";
					std::cout << "\n";
					++nb;
				}
				std::cout << i << " " << indices[i] << "\n";
			}
			std::cout << bs << " <" << cbatch << ", " << uniques << ">\n\n";
		}
	}
	return overallInvocations;
}

struct InvocationTimingResult
{
	uint32_t multiprocess;
	uint32_t warp;
	//uint64_t timestemp;
	uint32_t timestemp;
	uint32_t mask;
	bool operator == (const InvocationTimingResult & other) const
	{
		return multiprocess == other.multiprocess && warp == other.warp 
			&& timestemp == other.timestemp && mask == other.mask;
			//&& timestemp == other.timestemp;
	}
	bool operator != (const InvocationTimingResult & other) const
	{
		return multiprocess != other.multiprocess || warp != other.warp ||
			timestemp != other.timestemp || mask != other.mask;
			//timestemp != other.timestemp;
	}
	bool operator < (const InvocationTimingResult & other) const
	{
		return multiprocess != other.multiprocess ? multiprocess < other.multiprocess :
			warp != other.warp ? warp < other.warp :
			timestemp != other.timestemp ? timestemp < other.timestemp :
			mask < other.mask;
			//timestemp < other.timestemp;
	}
};
namespace std
{
	template<>
	class hash<InvocationTimingResult>
	{
	public:
		std::size_t operator()(InvocationTimingResult const& s) const noexcept
		{
			return std::hash<uint32_t>{}(s.multiprocess) ^ std::hash<uint32_t>{}(s.warp) 
				^ std::hash<uint32_t>{}(s.timestemp) ^ std::hash<uint32_t>{}(s.mask);
				//^ std::hash<uint64_t>{}(s.timestemp);
		}
	};
}
void InvocationChecker::draw(GLuint camera_uniform_buffer, GLsizei n) const
{
	//n = 96;
	glBindVertexArray(vao);
	glUseProgram(prog_invo);

	glBindBufferBase(GL_UNIFORM_BUFFER, 0U, camera_uniform_buffer);

	glEnable(GL_DEPTH_TEST);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, vertex_invocation_counter_buffer);

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, vertex_invocation_timing_buffer);

	//glBindBuffer(GL_SHADER_STORAGE_BUFFER, vertex_invocation_counter_buffer);
	GL::throw_error();
	std::vector<uint32_t> invocations(num_vertices, 0);


	std::vector<InvocationTimingResult> invocation_timings(num_indices/3);

	//for (GLsizei n = stepsize; n < num_indices + stepsize; n += stepsize)
	{

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_BUFFER, color_buffer_texture);
		GL::throw_error();

		//glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		n = std::min(n, num_indices);
		int zero = 0;
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, vertex_invocation_counter_buffer);
		glClearBufferSubData(GL_SHADER_STORAGE_BUFFER, GL_R32UI, 0, num_vertices * 4, GL_RED, GL_UNSIGNED_INT, &zero);
		GL::throw_error();

		//glBindBuffer(GL_SHADER_STORAGE_BUFFER, vertex_invocation_timing_buffer);
		//uint32_t zero4[] = { 0,0,0,0 };
		//glClearBufferSubData(GL_SHADER_STORAGE_BUFFER, GL_RGBA32UI, 0, num_indices / 3 * 4 * 4, GL_RGBA, GL_UNSIGNED_INT, zero4);
		//GL::throw_error();

		//glUniform1ui(2, maxvalence);
		//GL::throw_error();

		glDrawElements(GL_TRIANGLES, n, GL_UNSIGNED_INT, nullptr);
		GL::throw_error();

		glGetNamedBufferSubData(vertex_invocation_timing_buffer, 0, num_indices / 3 * 4 * 4, &invocation_timings[0]);
		GL::throw_error();

		glGetNamedBufferSubData(vertex_invocation_counter_buffer, 0, num_vertices * 4, &invocations[0]);
		GL::throw_error();

		//return;
		/*
		// find warp invocations

		// sort each
		for (size_t v = 0; v < num_vertices; ++v)
		{
			uint32_t tn = invocations[v];
			std::sort(begin(invocation_timings) + maxvalence * v, begin(invocation_timings) + maxvalence * v + tn);
		}

		std::unordered_map<InvocationTimingResult, uint32_t> invocation_combiner;
		std::unordered_multimap <InvocationTimingResult, uint32_t> invocation_tracker;

		for (size_t v = 0; v < num_vertices; ++v)
			for (size_t i = 0; i < invocations[v]; ++i)
			{
				InvocationTimingResult c = invocation_timings[maxvalence*v + i];
				auto found = invocation_combiner.find(c);
				if (found != end(invocation_combiner))
					++found->second;
				else
					invocation_combiner[c] = 1;
			}

		// assing primitves to invocation
		std::vector<uint32_t> perPrimitiveBatchId(n / 3);
		std::vector<InvocationTimingResult> perPrimitiveInvocation(n / 3);
		std::vector<InvocationTimingResult> last(1, { 0,0,0 });
		std::vector<InvocationTimingResult> interlast;
		std::vector<InvocationTimingResult> inter1, inter2;
		uint32_t nextassign = 0u;
		uint32_t batchId = 0u-1u;
		for (uint32_t p = 0; p < static_cast<uint32_t>(n) / 3; ++p)
		{
			uint32_t pids[] = { indices[3 * p], indices[3 * p + 1], indices[3 * p + 2] };
			uint32_t invs[] = { invocations[pids[0]], invocations[pids[1]], invocations[pids[2]] };

			//find potentials
			size_t maxelements = *std::max_element(invs, invs + 3);
			inter1.resize(maxelements); inter2.resize(maxelements);
			auto pres = std::set_intersection(begin(invocation_timings) + maxvalence * pids[0], begin(invocation_timings) + maxvalence * pids[0] + invs[0],
				begin(invocation_timings) + maxvalence * pids[1], begin(invocation_timings) + maxvalence * pids[1] + invs[1], inter1.begin());
			auto pres2 = std::set_intersection(begin(invocation_timings) + maxvalence * pids[2], begin(invocation_timings) + maxvalence * pids[2] + invs[2],
				inter1.begin(), pres, inter2.begin());

			size_t n_intersections = pres2 - inter2.begin();
			size_t orig_n_intersections = n_intersections;
			n_intersections = 0;
			//remove already used up and duplicates (same vertex shaded multiple times in same batch)
			for (size_t i = 0; i < orig_n_intersections; ++i)
			{
				if (invocation_combiner[inter2[i]] > 0)
				{
					if (n_intersections == 0 || inter2[i] != inter2[n_intersections-1])
						inter2[n_intersections++] = inter2[i];
				}
			}
			if(n_intersections != orig_n_intersections)
			{
				pres2 = begin(inter2) + n_intersections;
				//std::sort(begin(inter2), pres2);

				if (n_intersections == 0 && orig_n_intersections > 0)
					throw std::runtime_error("non connected batch found!");
			}
			if (n_intersections == 0)
				throw std::runtime_error((std::string("no unified called for primitive ") + std::to_string(p)).c_str());

			//check with last
			interlast.resize(std::min(n_intersections, last.size()));
			auto pinterlast = std::set_intersection(begin(inter2), pres2, begin(last), end(last), begin(interlast));

			size_t n_withlast = pinterlast - begin(interlast);
			if (n_withlast == 0)
			{
				if(last.size() != 1)
				{ 
					//new batch, need to make best guess with old ones
					uint32_t needtoassign = p - nextassign;
					for (auto & l : last)
					{
						if (invocation_combiner[l] == needtoassign * 3)
						{
							//found matching
							for (; nextassign < p; ++nextassign)
							{
								perPrimitiveInvocation[nextassign] = l;
								perPrimitiveBatchId[nextassign] = batchId;
								invocation_tracker.insert(std::make_pair(l, nextassign));
							}
							last[0] = l;
							needtoassign = 0;
							break;
						}
					}

					if(needtoassign != 0)
						throw std::runtime_error((std::string("no unified call for primitive ") + std::to_string(nextassign) + " - " + std::to_string(p)).c_str());
				}
				invocation_combiner[last[0]] = 0;
				++batchId;
				last.resize(0);

				// entire intersection is new last
				inter2.swap(interlast);
				pinterlast = pres2;
				n_withlast = n_intersections;
			}

			if (n_withlast == 1)
			{
				// perform assign
				InvocationTimingResult assign = interlast[0];
				for (; nextassign <= p; ++nextassign)
				{
					perPrimitiveInvocation[nextassign] = assign;
					perPrimitiveBatchId[nextassign] = batchId;
					invocation_tracker.insert(std::make_pair(assign, nextassign));
				}
			}
			last.swap(interlast);
			last.resize(n_withlast);
		}

		if(last.size() > 1)
			throw std::runtime_error("could not assign warp calls ");*/

		// now directly form fragment shader
		size_t overallinvo = 0;
		std::vector<uint32_t> perPrimitiveBatchId(n / 3+1);
		std::vector<size_t> perBatchSimulatedInvocations;
		uint32_t batchId = 0u - 1u;
		InvocationTimingResult lastInvo = { 0,0,0,0 };
		std::vector<uint32_t> simulatedInvocation(num_vertices, 0);
		uint32_t batchStart = 0;
		for (uint32_t p = 0; p < static_cast<uint32_t>(n) / 3 + 1; ++p)
		{
			if (p == static_cast<uint32_t>(n) / 3 || invocation_timings[p] != lastInvo)
			{
				++batchId;
				if(3 * p - batchStart > 0)
				{
					size_t invos =  simulateReuse(&simulatedInvocation[0], nullptr, num_vertices, &indices[batchStart], 3 * p - batchStart);
					overallinvo += invos;
					batchStart = 3*p;
					perBatchSimulatedInvocations.push_back(invos);
				}
			}
			if(p < static_cast<uint32_t>(n) / 3)
			{
				lastInvo = invocation_timings[p];
				perPrimitiveBatchId[p] = batchId;
			}
		}
		perPrimitiveBatchId.back() = 0xFFFFFFFF;

		//TODO: use perPrimitiveBatchId to visualize and check simulation

		// for now simply output
		if (false)
		{
			uint32_t last = perPrimitiveBatchId[0];
			uint32_t primitiveCount = 0;
			for (uint32_t p = 0; p <= static_cast<uint32_t>(n) / 3; ++p)
			{
				if (perPrimitiveBatchId[p] != last)
				{
					auto info = invocation_timings[p - 1];
					std::cout << "[" << last << "] -- num: " << primitiveCount <<
						" loc: " << info.multiprocess << " " << info.warp << "  actives: " << info.mask << " sim calls: " << perBatchSimulatedInvocations[last];
					if (perBatchSimulatedInvocations[last] != info.mask)
						std::cout << " ###";
					std::cout << "\n";
					last = perPrimitiveBatchId[p];
					primitiveCount = 0;
				}
				if (p < static_cast<uint32_t>(n) / 3)
				{
					++primitiveCount;
					std::cout << p << ": " << indices[3 * p] << " " << indices[3 * p + 1] << " " << indices[3 * p + 2] << "\n";
				}
			}
			//std::cout << "[" << last << "] ------------ " << primitiveCount << "\n";

			std::cout << "\nreal invos / simulated per batch:\n";
			size_t sumreal = 0, sumsim = 0;
			for (size_t v = 0; v < num_vertices; ++v)
			{
				if (invocations[v] != simulatedInvocation[v])
				{
					std::cout << v << ": " << invocations[v] << " " << simulatedInvocation[v] << "\n";
				}
				sumsim += simulatedInvocation[v];
				sumreal += invocations[v];
			}
			std::cout << "real overall: " << sumreal << " simulated: " << sumsim << "\n";
			std::cout << "shading rate: " << (3.0*sumreal)/num_indices << " simulated: "<< (3.0*sumsim) / num_indices << "\n\n";
		}

		//size_t refs = 0, counts = 0;
		//for (size_t i = 0; i < num_vertices; ++i)
		//{
		//	if (invocations[i] != 0)
		//	{
		//		++refs;
		//		counts += invocations[i];
		//		//std::cout << i << ": " << invocations[i] << "\n";
		//	}
		//}
		//std::cout << "res: " << n << " " << refs << " " << counts << "\n";

		std::vector<std::uint32_t> siminv(num_vertices);


		//void compareReuse(std::uint32_t* sim_inv, const std::uint32_t* inv_counters, std::size_t num_vertices, const std::uint32_t* indices, std::size_t num_indices)
		//simulateReuse(&siminv[0], &invocations[0], num_vertices, &indices[0], n, &perPrimitiveBatchId[0]);
	}


	GL::throw_error();
}

