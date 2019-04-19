#pragma once

#include "BatchSimulator.h"
#include <memory>

enum VertexReuseSimType : int
{
	VRS_NV_DX = 0,
	VRS_NV_GL = 1,
	VRS_ATI = 2,
	VRS_INTEL_EXPERIMENTAL = 3,
	VRS_STATIC_WARP = 4,
	VRS_DYNAMIC_BLOCK = 5
};
inline const char* VertexReuseName(VertexReuseSimType t)
{
	switch (t)
	{
	case VRS_NV_DX:
		return "NVIDIA_DX (dyn, 96, 32, FIFO +/-42)";
	case VRS_NV_GL:
		return "NVIDIA_GL (dyn, 96, 32, FIFO 42)";
	case VRS_ATI:
		return "ATI_BASIC (stat, 384, x, LRU 15)";
	case VRS_INTEL_EXPERIMENTAL:
		return "INTEL_LOWER_BOUND (dyn, 1791, 128, ALL)";
	case VRS_STATIC_WARP:
		return "CURE warp (stat, 96, 32, ALL)";
	case VRS_DYNAMIC_BLOCK:
		return "CURE block (dyn, 1023, 256, ALL)";
	}
	return "Unknown Reuse Type";
}

template<VertexReuseSimType t>
struct BatchSimulationParameters;

template<>
struct BatchSimulationParameters<VRS_NV_DX>
{
	static const uint32_t BatchIndices = 96,
		BatchVertices = 32,
		HardReset = 0xFFFFFFFF;
	static const bool TriangleBounds = true;
	using Simulation = NVDxCacheSim;
};
template<>
struct BatchSimulationParameters<VRS_NV_GL>
{
	static const uint32_t BatchIndices = 96,
		BatchVertices = 32,
		HardReset = 0xFFFFFFFF;
	static const bool TriangleBounds = true;
	using Simulation = NVGLCacheSim;
};
template<>
struct BatchSimulationParameters<VRS_ATI>
{
	static const uint32_t BatchIndices = 384,
		BatchVertices = 64,
		HardReset = 384;
	static const bool TriangleBounds = false;
	using Simulation = LRUCacheSim<15>;
};
template<>
struct BatchSimulationParameters<VRS_INTEL_EXPERIMENTAL>
{
	static const uint32_t BatchIndices = 1791,
		BatchVertices = 128,
		HardReset = 0xFFFFFFFF;
	static const bool TriangleBounds = true;
	using Simulation = FIFOCacheSim<ForeverCacheEntry>;
};

template<>
struct BatchSimulationParameters<VRS_STATIC_WARP>
{
	static const uint32_t BatchIndices = 96,
		BatchVertices = 32,
		HardReset = 0xFFFFFFFF;
	static const bool TriangleBounds = true;
	using Simulation = FIFOCacheSim<ForeverCacheEntry>;
};

template<>
struct BatchSimulationParameters<VRS_DYNAMIC_BLOCK>
{
	static const uint32_t BatchIndices = 1023,
		BatchVertices = 256,
		HardReset = 0xFFFFFFFF;
	static const bool TriangleBounds = true;
	using Simulation = FIFOCacheSim<ForeverCacheEntry>;
};

template<VertexReuseSimType Type, typename BatchEnd>
uint32_t simulateBatch(const std::uint32_t* indices, std::size_t num_indices,
	BatchEnd batchend)
{
	using P = BatchSimulationParameters<Type>;
	return simulateBatch<P::Simulation>(P::BatchIndices, P::BatchVertices,
		indices, num_indices,
		P::TriangleBounds, P::HardReset,
		batchend);
}

template<typename BatchEnd>
uint32_t simulateBatch(VertexReuseSimType t, const std::uint32_t* indices, std::size_t num_indices,
	BatchEnd batchend)
{
	switch (t)
	{
	case VRS_NV_DX:
		return simulateBatch<VRS_NV_DX>(indices, num_indices, batchend);
	case VRS_NV_GL:
		return simulateBatch<VRS_NV_GL>(indices, num_indices, batchend);
	case VRS_ATI:
		return simulateBatch<VRS_ATI>(indices, num_indices, batchend);
	case VRS_INTEL_EXPERIMENTAL:
		return simulateBatch<VRS_INTEL_EXPERIMENTAL>(indices, num_indices, batchend);
	case VRS_STATIC_WARP:
		return simulateBatch<VRS_STATIC_WARP>(indices, num_indices, batchend);
	case VRS_DYNAMIC_BLOCK:
		return simulateBatch<VRS_DYNAMIC_BLOCK>(indices, num_indices, batchend);
	}
	return 0;
}

inline uint32_t simulateInvocations(VertexReuseSimType type, const std::uint32_t* indices, std::size_t num_indices)
{
	return simulateBatch(type, indices, num_indices, [](uint32_t, uint32_t, auto) {});
}



class IBatchState
{
public:
	virtual int32_t canAddTriangle(const uint32_t indices[3]) = 0;
	virtual int32_t canAddTriangle(const uint32_t* indices, uint32_t offset) = 0;

	virtual void addTriangle(const uint32_t indices[3]) = 0;
	virtual void addTriangle(const uint32_t* indices, uint32_t offset) = 0;

	virtual bool isInCache(uint32_t id) const = 0;

	virtual void endBatch(bool hard) = 0;
	virtual void reset() = 0;

	virtual uint32_t getInvocations() const = 0;

	virtual ~IBatchState() {};
};


template<class CacheSim>
class BatchStateImpl : public IBatchState
{
	BatchState<CacheSim> bStateSim;
public:
	BatchStateImpl(uint32_t batchIndices, uint32_t batchVertices, uint32_t hard_reset, bool triangle_bounds) :
		bStateSim(batchIndices, batchVertices, hard_reset, triangle_bounds)
	{
	}
	int32_t canAddTriangle(const uint32_t indices[3]) override
	{
		return bStateSim.canAddTriangle(indices);
	}
	int32_t canAddTriangle(const uint32_t* indices, uint32_t offset = 0) override
	{
		return bStateSim.canAddTriangle(indices, offset);
	}

	void addTriangle(const uint32_t indices[3]) override
	{
		return bStateSim.addTriangle(indices, [](uint32_t, uint32_t, auto) {});
	}
	void addTriangle(const uint32_t* indices, uint32_t offset = 0) override
	{
		return bStateSim.addTriangle(indices, offset, [](uint32_t, uint32_t, auto) {});
	}

	bool isInCache(uint32_t id) const override
	{
		return bStateSim.isInCache(id);
	}

	void endBatch(bool hard) override
	{
		return bStateSim.endBatch(hard, [](uint32_t, uint32_t, auto) {});
	}
	void reset() override
	{
		return bStateSim.reset();
	}

	uint32_t getInvocations() const override
	{
		return bStateSim.getInvocations();
	}

};


template<VertexReuseSimType Type>
std::unique_ptr<IBatchState> createBatchSim()
{
	using P = BatchSimulationParameters<Type>;
	return std::make_unique<BatchStateImpl<P::Simulation>>(P::BatchIndices, P::BatchVertices, P::HardReset, P::TriangleBounds);
}

inline std::unique_ptr<IBatchState> createBatchSim(VertexReuseSimType t)
{
	switch (t)
	{
	case VRS_NV_DX:
		return createBatchSim<VRS_NV_DX>();
	case VRS_NV_GL:
		return createBatchSim<VRS_NV_GL>();
	case VRS_ATI:
		return createBatchSim<VRS_ATI>();
	case VRS_INTEL_EXPERIMENTAL:
		return createBatchSim<VRS_INTEL_EXPERIMENTAL>();
	case VRS_STATIC_WARP:
		return createBatchSim<VRS_STATIC_WARP>();
	case VRS_DYNAMIC_BLOCK:
		return createBatchSim<VRS_DYNAMIC_BLOCK>();
	}
	return nullptr;
}

