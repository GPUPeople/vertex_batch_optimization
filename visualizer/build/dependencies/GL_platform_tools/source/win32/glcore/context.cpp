


#include <stdexcept>

#include "context.h"


namespace
{
	__declspec(thread) const glcoreContext* context = nullptr;
}

extern "C"
{
	glcoreContext::glcoreContext()
	{
		ActiveShaderProgram = reinterpret_cast<decltype(glActiveShaderProgram)*>(wglGetProcAddress("glActiveShaderProgram"));
		ActiveTexture = reinterpret_cast<decltype(glActiveTexture)*>(wglGetProcAddress("glActiveTexture"));
		AttachShader = reinterpret_cast<decltype(glAttachShader)*>(wglGetProcAddress("glAttachShader"));
		BeginConditionalRender = reinterpret_cast<decltype(glBeginConditionalRender)*>(wglGetProcAddress("glBeginConditionalRender"));
		BeginQuery = reinterpret_cast<decltype(glBeginQuery)*>(wglGetProcAddress("glBeginQuery"));
		BeginQueryIndexed = reinterpret_cast<decltype(glBeginQueryIndexed)*>(wglGetProcAddress("glBeginQueryIndexed"));
		BeginTransformFeedback = reinterpret_cast<decltype(glBeginTransformFeedback)*>(wglGetProcAddress("glBeginTransformFeedback"));
		BindAttribLocation = reinterpret_cast<decltype(glBindAttribLocation)*>(wglGetProcAddress("glBindAttribLocation"));
		BindBuffer = reinterpret_cast<decltype(glBindBuffer)*>(wglGetProcAddress("glBindBuffer"));
		BindBufferBase = reinterpret_cast<decltype(glBindBufferBase)*>(wglGetProcAddress("glBindBufferBase"));
		BindBufferRange = reinterpret_cast<decltype(glBindBufferRange)*>(wglGetProcAddress("glBindBufferRange"));
		BindBuffersBase = reinterpret_cast<decltype(glBindBuffersBase)*>(wglGetProcAddress("glBindBuffersBase"));
		BindBuffersRange = reinterpret_cast<decltype(glBindBuffersRange)*>(wglGetProcAddress("glBindBuffersRange"));
		BindFragDataLocation = reinterpret_cast<decltype(glBindFragDataLocation)*>(wglGetProcAddress("glBindFragDataLocation"));
		BindFragDataLocationIndexed = reinterpret_cast<decltype(glBindFragDataLocationIndexed)*>(wglGetProcAddress("glBindFragDataLocationIndexed"));
		BindFramebuffer = reinterpret_cast<decltype(glBindFramebuffer)*>(wglGetProcAddress("glBindFramebuffer"));
		BindImageTexture = reinterpret_cast<decltype(glBindImageTexture)*>(wglGetProcAddress("glBindImageTexture"));
		BindImageTextures = reinterpret_cast<decltype(glBindImageTextures)*>(wglGetProcAddress("glBindImageTextures"));
		BindProgramPipeline = reinterpret_cast<decltype(glBindProgramPipeline)*>(wglGetProcAddress("glBindProgramPipeline"));
		BindRenderbuffer = reinterpret_cast<decltype(glBindRenderbuffer)*>(wglGetProcAddress("glBindRenderbuffer"));
		BindSampler = reinterpret_cast<decltype(glBindSampler)*>(wglGetProcAddress("glBindSampler"));
		BindSamplers = reinterpret_cast<decltype(glBindSamplers)*>(wglGetProcAddress("glBindSamplers"));
		BindTextureUnit = reinterpret_cast<decltype(glBindTextureUnit)*>(wglGetProcAddress("glBindTextureUnit"));
		BindTextures = reinterpret_cast<decltype(glBindTextures)*>(wglGetProcAddress("glBindTextures"));
		BindTransformFeedback = reinterpret_cast<decltype(glBindTransformFeedback)*>(wglGetProcAddress("glBindTransformFeedback"));
		BindVertexArray = reinterpret_cast<decltype(glBindVertexArray)*>(wglGetProcAddress("glBindVertexArray"));
		BindVertexBuffer = reinterpret_cast<decltype(glBindVertexBuffer)*>(wglGetProcAddress("glBindVertexBuffer"));
		BindVertexBuffers = reinterpret_cast<decltype(glBindVertexBuffers)*>(wglGetProcAddress("glBindVertexBuffers"));
		BlendColor = reinterpret_cast<decltype(glBlendColor)*>(wglGetProcAddress("glBlendColor"));
		BlendEquation = reinterpret_cast<decltype(glBlendEquation)*>(wglGetProcAddress("glBlendEquation"));
		BlendEquationSeparate = reinterpret_cast<decltype(glBlendEquationSeparate)*>(wglGetProcAddress("glBlendEquationSeparate"));
		BlendEquationSeparatei = reinterpret_cast<decltype(glBlendEquationSeparatei)*>(wglGetProcAddress("glBlendEquationSeparatei"));
		BlendEquationi = reinterpret_cast<decltype(glBlendEquationi)*>(wglGetProcAddress("glBlendEquationi"));
		BlendFuncSeparate = reinterpret_cast<decltype(glBlendFuncSeparate)*>(wglGetProcAddress("glBlendFuncSeparate"));
		BlendFuncSeparatei = reinterpret_cast<decltype(glBlendFuncSeparatei)*>(wglGetProcAddress("glBlendFuncSeparatei"));
		BlendFunci = reinterpret_cast<decltype(glBlendFunci)*>(wglGetProcAddress("glBlendFunci"));
		BlitFramebuffer = reinterpret_cast<decltype(glBlitFramebuffer)*>(wglGetProcAddress("glBlitFramebuffer"));
		BlitNamedFramebuffer = reinterpret_cast<decltype(glBlitNamedFramebuffer)*>(wglGetProcAddress("glBlitNamedFramebuffer"));
		BufferData = reinterpret_cast<decltype(glBufferData)*>(wglGetProcAddress("glBufferData"));
		BufferStorage = reinterpret_cast<decltype(glBufferStorage)*>(wglGetProcAddress("glBufferStorage"));
		BufferSubData = reinterpret_cast<decltype(glBufferSubData)*>(wglGetProcAddress("glBufferSubData"));
		CheckFramebufferStatus = reinterpret_cast<decltype(glCheckFramebufferStatus)*>(wglGetProcAddress("glCheckFramebufferStatus"));
		CheckNamedFramebufferStatus = reinterpret_cast<decltype(glCheckNamedFramebufferStatus)*>(wglGetProcAddress("glCheckNamedFramebufferStatus"));
		ClampColor = reinterpret_cast<decltype(glClampColor)*>(wglGetProcAddress("glClampColor"));
		ClearBufferData = reinterpret_cast<decltype(glClearBufferData)*>(wglGetProcAddress("glClearBufferData"));
		ClearBufferSubData = reinterpret_cast<decltype(glClearBufferSubData)*>(wglGetProcAddress("glClearBufferSubData"));
		ClearBufferfi = reinterpret_cast<decltype(glClearBufferfi)*>(wglGetProcAddress("glClearBufferfi"));
		ClearBufferfv = reinterpret_cast<decltype(glClearBufferfv)*>(wglGetProcAddress("glClearBufferfv"));
		ClearBufferiv = reinterpret_cast<decltype(glClearBufferiv)*>(wglGetProcAddress("glClearBufferiv"));
		ClearBufferuiv = reinterpret_cast<decltype(glClearBufferuiv)*>(wglGetProcAddress("glClearBufferuiv"));
		ClearDepthf = reinterpret_cast<decltype(glClearDepthf)*>(wglGetProcAddress("glClearDepthf"));
		ClearNamedBufferData = reinterpret_cast<decltype(glClearNamedBufferData)*>(wglGetProcAddress("glClearNamedBufferData"));
		ClearNamedBufferSubData = reinterpret_cast<decltype(glClearNamedBufferSubData)*>(wglGetProcAddress("glClearNamedBufferSubData"));
		ClearNamedFramebufferfi = reinterpret_cast<decltype(glClearNamedFramebufferfi)*>(wglGetProcAddress("glClearNamedFramebufferfi"));
		ClearNamedFramebufferfv = reinterpret_cast<decltype(glClearNamedFramebufferfv)*>(wglGetProcAddress("glClearNamedFramebufferfv"));
		ClearNamedFramebufferiv = reinterpret_cast<decltype(glClearNamedFramebufferiv)*>(wglGetProcAddress("glClearNamedFramebufferiv"));
		ClearNamedFramebufferuiv = reinterpret_cast<decltype(glClearNamedFramebufferuiv)*>(wglGetProcAddress("glClearNamedFramebufferuiv"));
		ClearTexImage = reinterpret_cast<decltype(glClearTexImage)*>(wglGetProcAddress("glClearTexImage"));
		ClearTexSubImage = reinterpret_cast<decltype(glClearTexSubImage)*>(wglGetProcAddress("glClearTexSubImage"));
		ClientWaitSync = reinterpret_cast<decltype(glClientWaitSync)*>(wglGetProcAddress("glClientWaitSync"));
		ClipControl = reinterpret_cast<decltype(glClipControl)*>(wglGetProcAddress("glClipControl"));
		ColorMaski = reinterpret_cast<decltype(glColorMaski)*>(wglGetProcAddress("glColorMaski"));
		CompileShader = reinterpret_cast<decltype(glCompileShader)*>(wglGetProcAddress("glCompileShader"));
		CompressedTexImage1D = reinterpret_cast<decltype(glCompressedTexImage1D)*>(wglGetProcAddress("glCompressedTexImage1D"));
		CompressedTexImage2D = reinterpret_cast<decltype(glCompressedTexImage2D)*>(wglGetProcAddress("glCompressedTexImage2D"));
		CompressedTexImage3D = reinterpret_cast<decltype(glCompressedTexImage3D)*>(wglGetProcAddress("glCompressedTexImage3D"));
		CompressedTexSubImage1D = reinterpret_cast<decltype(glCompressedTexSubImage1D)*>(wglGetProcAddress("glCompressedTexSubImage1D"));
		CompressedTexSubImage2D = reinterpret_cast<decltype(glCompressedTexSubImage2D)*>(wglGetProcAddress("glCompressedTexSubImage2D"));
		CompressedTexSubImage3D = reinterpret_cast<decltype(glCompressedTexSubImage3D)*>(wglGetProcAddress("glCompressedTexSubImage3D"));
		CompressedTextureSubImage1D = reinterpret_cast<decltype(glCompressedTextureSubImage1D)*>(wglGetProcAddress("glCompressedTextureSubImage1D"));
		CompressedTextureSubImage2D = reinterpret_cast<decltype(glCompressedTextureSubImage2D)*>(wglGetProcAddress("glCompressedTextureSubImage2D"));
		CompressedTextureSubImage3D = reinterpret_cast<decltype(glCompressedTextureSubImage3D)*>(wglGetProcAddress("glCompressedTextureSubImage3D"));
		CopyBufferSubData = reinterpret_cast<decltype(glCopyBufferSubData)*>(wglGetProcAddress("glCopyBufferSubData"));
		CopyImageSubData = reinterpret_cast<decltype(glCopyImageSubData)*>(wglGetProcAddress("glCopyImageSubData"));
		CopyNamedBufferSubData = reinterpret_cast<decltype(glCopyNamedBufferSubData)*>(wglGetProcAddress("glCopyNamedBufferSubData"));
		CopyTexSubImage3D = reinterpret_cast<decltype(glCopyTexSubImage3D)*>(wglGetProcAddress("glCopyTexSubImage3D"));
		CopyTextureSubImage1D = reinterpret_cast<decltype(glCopyTextureSubImage1D)*>(wglGetProcAddress("glCopyTextureSubImage1D"));
		CopyTextureSubImage2D = reinterpret_cast<decltype(glCopyTextureSubImage2D)*>(wglGetProcAddress("glCopyTextureSubImage2D"));
		CopyTextureSubImage3D = reinterpret_cast<decltype(glCopyTextureSubImage3D)*>(wglGetProcAddress("glCopyTextureSubImage3D"));
		CreateBuffers = reinterpret_cast<decltype(glCreateBuffers)*>(wglGetProcAddress("glCreateBuffers"));
		CreateFramebuffers = reinterpret_cast<decltype(glCreateFramebuffers)*>(wglGetProcAddress("glCreateFramebuffers"));
		CreateProgram = reinterpret_cast<decltype(glCreateProgram)*>(wglGetProcAddress("glCreateProgram"));
		CreateProgramPipelines = reinterpret_cast<decltype(glCreateProgramPipelines)*>(wglGetProcAddress("glCreateProgramPipelines"));
		CreateQueries = reinterpret_cast<decltype(glCreateQueries)*>(wglGetProcAddress("glCreateQueries"));
		CreateRenderbuffers = reinterpret_cast<decltype(glCreateRenderbuffers)*>(wglGetProcAddress("glCreateRenderbuffers"));
		CreateSamplers = reinterpret_cast<decltype(glCreateSamplers)*>(wglGetProcAddress("glCreateSamplers"));
		CreateShader = reinterpret_cast<decltype(glCreateShader)*>(wglGetProcAddress("glCreateShader"));
		CreateShaderProgramv = reinterpret_cast<decltype(glCreateShaderProgramv)*>(wglGetProcAddress("glCreateShaderProgramv"));
		CreateTextures = reinterpret_cast<decltype(glCreateTextures)*>(wglGetProcAddress("glCreateTextures"));
		CreateTransformFeedbacks = reinterpret_cast<decltype(glCreateTransformFeedbacks)*>(wglGetProcAddress("glCreateTransformFeedbacks"));
		CreateVertexArrays = reinterpret_cast<decltype(glCreateVertexArrays)*>(wglGetProcAddress("glCreateVertexArrays"));
		DebugMessageCallback = reinterpret_cast<decltype(glDebugMessageCallback)*>(wglGetProcAddress("glDebugMessageCallback"));
		DebugMessageControl = reinterpret_cast<decltype(glDebugMessageControl)*>(wglGetProcAddress("glDebugMessageControl"));
		DebugMessageInsert = reinterpret_cast<decltype(glDebugMessageInsert)*>(wglGetProcAddress("glDebugMessageInsert"));
		DeleteBuffers = reinterpret_cast<decltype(glDeleteBuffers)*>(wglGetProcAddress("glDeleteBuffers"));
		DeleteFramebuffers = reinterpret_cast<decltype(glDeleteFramebuffers)*>(wglGetProcAddress("glDeleteFramebuffers"));
		DeleteProgram = reinterpret_cast<decltype(glDeleteProgram)*>(wglGetProcAddress("glDeleteProgram"));
		DeleteProgramPipelines = reinterpret_cast<decltype(glDeleteProgramPipelines)*>(wglGetProcAddress("glDeleteProgramPipelines"));
		DeleteQueries = reinterpret_cast<decltype(glDeleteQueries)*>(wglGetProcAddress("glDeleteQueries"));
		DeleteRenderbuffers = reinterpret_cast<decltype(glDeleteRenderbuffers)*>(wglGetProcAddress("glDeleteRenderbuffers"));
		DeleteSamplers = reinterpret_cast<decltype(glDeleteSamplers)*>(wglGetProcAddress("glDeleteSamplers"));
		DeleteShader = reinterpret_cast<decltype(glDeleteShader)*>(wglGetProcAddress("glDeleteShader"));
		DeleteSync = reinterpret_cast<decltype(glDeleteSync)*>(wglGetProcAddress("glDeleteSync"));
		DeleteTransformFeedbacks = reinterpret_cast<decltype(glDeleteTransformFeedbacks)*>(wglGetProcAddress("glDeleteTransformFeedbacks"));
		DeleteVertexArrays = reinterpret_cast<decltype(glDeleteVertexArrays)*>(wglGetProcAddress("glDeleteVertexArrays"));
		DepthRangeArrayv = reinterpret_cast<decltype(glDepthRangeArrayv)*>(wglGetProcAddress("glDepthRangeArrayv"));
		DepthRangeIndexed = reinterpret_cast<decltype(glDepthRangeIndexed)*>(wglGetProcAddress("glDepthRangeIndexed"));
		DepthRangef = reinterpret_cast<decltype(glDepthRangef)*>(wglGetProcAddress("glDepthRangef"));
		DetachShader = reinterpret_cast<decltype(glDetachShader)*>(wglGetProcAddress("glDetachShader"));
		DisableVertexArrayAttrib = reinterpret_cast<decltype(glDisableVertexArrayAttrib)*>(wglGetProcAddress("glDisableVertexArrayAttrib"));
		DisableVertexAttribArray = reinterpret_cast<decltype(glDisableVertexAttribArray)*>(wglGetProcAddress("glDisableVertexAttribArray"));
		Disablei = reinterpret_cast<decltype(glDisablei)*>(wglGetProcAddress("glDisablei"));
		DispatchCompute = reinterpret_cast<decltype(glDispatchCompute)*>(wglGetProcAddress("glDispatchCompute"));
		DispatchComputeIndirect = reinterpret_cast<decltype(glDispatchComputeIndirect)*>(wglGetProcAddress("glDispatchComputeIndirect"));
		DrawArraysIndirect = reinterpret_cast<decltype(glDrawArraysIndirect)*>(wglGetProcAddress("glDrawArraysIndirect"));
		DrawArraysInstanced = reinterpret_cast<decltype(glDrawArraysInstanced)*>(wglGetProcAddress("glDrawArraysInstanced"));
		DrawArraysInstancedBaseInstance = reinterpret_cast<decltype(glDrawArraysInstancedBaseInstance)*>(wglGetProcAddress("glDrawArraysInstancedBaseInstance"));
		DrawBuffers = reinterpret_cast<decltype(glDrawBuffers)*>(wglGetProcAddress("glDrawBuffers"));
		DrawElementsBaseVertex = reinterpret_cast<decltype(glDrawElementsBaseVertex)*>(wglGetProcAddress("glDrawElementsBaseVertex"));
		DrawElementsIndirect = reinterpret_cast<decltype(glDrawElementsIndirect)*>(wglGetProcAddress("glDrawElementsIndirect"));
		DrawElementsInstanced = reinterpret_cast<decltype(glDrawElementsInstanced)*>(wglGetProcAddress("glDrawElementsInstanced"));
		DrawElementsInstancedBaseInstance = reinterpret_cast<decltype(glDrawElementsInstancedBaseInstance)*>(wglGetProcAddress("glDrawElementsInstancedBaseInstance"));
		DrawElementsInstancedBaseVertex = reinterpret_cast<decltype(glDrawElementsInstancedBaseVertex)*>(wglGetProcAddress("glDrawElementsInstancedBaseVertex"));
		DrawElementsInstancedBaseVertexBaseInstance = reinterpret_cast<decltype(glDrawElementsInstancedBaseVertexBaseInstance)*>(wglGetProcAddress("glDrawElementsInstancedBaseVertexBaseInstance"));
		DrawRangeElements = reinterpret_cast<decltype(glDrawRangeElements)*>(wglGetProcAddress("glDrawRangeElements"));
		DrawRangeElementsBaseVertex = reinterpret_cast<decltype(glDrawRangeElementsBaseVertex)*>(wglGetProcAddress("glDrawRangeElementsBaseVertex"));
		DrawTransformFeedback = reinterpret_cast<decltype(glDrawTransformFeedback)*>(wglGetProcAddress("glDrawTransformFeedback"));
		DrawTransformFeedbackInstanced = reinterpret_cast<decltype(glDrawTransformFeedbackInstanced)*>(wglGetProcAddress("glDrawTransformFeedbackInstanced"));
		DrawTransformFeedbackStream = reinterpret_cast<decltype(glDrawTransformFeedbackStream)*>(wglGetProcAddress("glDrawTransformFeedbackStream"));
		DrawTransformFeedbackStreamInstanced = reinterpret_cast<decltype(glDrawTransformFeedbackStreamInstanced)*>(wglGetProcAddress("glDrawTransformFeedbackStreamInstanced"));
		EnableVertexArrayAttrib = reinterpret_cast<decltype(glEnableVertexArrayAttrib)*>(wglGetProcAddress("glEnableVertexArrayAttrib"));
		EnableVertexAttribArray = reinterpret_cast<decltype(glEnableVertexAttribArray)*>(wglGetProcAddress("glEnableVertexAttribArray"));
		Enablei = reinterpret_cast<decltype(glEnablei)*>(wglGetProcAddress("glEnablei"));
		EndConditionalRender = reinterpret_cast<decltype(glEndConditionalRender)*>(wglGetProcAddress("glEndConditionalRender"));
		EndQuery = reinterpret_cast<decltype(glEndQuery)*>(wglGetProcAddress("glEndQuery"));
		EndQueryIndexed = reinterpret_cast<decltype(glEndQueryIndexed)*>(wglGetProcAddress("glEndQueryIndexed"));
		EndTransformFeedback = reinterpret_cast<decltype(glEndTransformFeedback)*>(wglGetProcAddress("glEndTransformFeedback"));
		FenceSync = reinterpret_cast<decltype(glFenceSync)*>(wglGetProcAddress("glFenceSync"));
		FlushMappedBufferRange = reinterpret_cast<decltype(glFlushMappedBufferRange)*>(wglGetProcAddress("glFlushMappedBufferRange"));
		FlushMappedNamedBufferRange = reinterpret_cast<decltype(glFlushMappedNamedBufferRange)*>(wglGetProcAddress("glFlushMappedNamedBufferRange"));
		FramebufferParameteri = reinterpret_cast<decltype(glFramebufferParameteri)*>(wglGetProcAddress("glFramebufferParameteri"));
		FramebufferRenderbuffer = reinterpret_cast<decltype(glFramebufferRenderbuffer)*>(wglGetProcAddress("glFramebufferRenderbuffer"));
		FramebufferTexture = reinterpret_cast<decltype(glFramebufferTexture)*>(wglGetProcAddress("glFramebufferTexture"));
		FramebufferTexture1D = reinterpret_cast<decltype(glFramebufferTexture1D)*>(wglGetProcAddress("glFramebufferTexture1D"));
		FramebufferTexture2D = reinterpret_cast<decltype(glFramebufferTexture2D)*>(wglGetProcAddress("glFramebufferTexture2D"));
		FramebufferTexture3D = reinterpret_cast<decltype(glFramebufferTexture3D)*>(wglGetProcAddress("glFramebufferTexture3D"));
		FramebufferTextureLayer = reinterpret_cast<decltype(glFramebufferTextureLayer)*>(wglGetProcAddress("glFramebufferTextureLayer"));
		GenBuffers = reinterpret_cast<decltype(glGenBuffers)*>(wglGetProcAddress("glGenBuffers"));
		GenFramebuffers = reinterpret_cast<decltype(glGenFramebuffers)*>(wglGetProcAddress("glGenFramebuffers"));
		GenProgramPipelines = reinterpret_cast<decltype(glGenProgramPipelines)*>(wglGetProcAddress("glGenProgramPipelines"));
		GenQueries = reinterpret_cast<decltype(glGenQueries)*>(wglGetProcAddress("glGenQueries"));
		GenRenderbuffers = reinterpret_cast<decltype(glGenRenderbuffers)*>(wglGetProcAddress("glGenRenderbuffers"));
		GenSamplers = reinterpret_cast<decltype(glGenSamplers)*>(wglGetProcAddress("glGenSamplers"));
		GenTransformFeedbacks = reinterpret_cast<decltype(glGenTransformFeedbacks)*>(wglGetProcAddress("glGenTransformFeedbacks"));
		GenVertexArrays = reinterpret_cast<decltype(glGenVertexArrays)*>(wglGetProcAddress("glGenVertexArrays"));
		GenerateMipmap = reinterpret_cast<decltype(glGenerateMipmap)*>(wglGetProcAddress("glGenerateMipmap"));
		GenerateTextureMipmap = reinterpret_cast<decltype(glGenerateTextureMipmap)*>(wglGetProcAddress("glGenerateTextureMipmap"));
		GetActiveAtomicCounterBufferiv = reinterpret_cast<decltype(glGetActiveAtomicCounterBufferiv)*>(wglGetProcAddress("glGetActiveAtomicCounterBufferiv"));
		GetActiveAttrib = reinterpret_cast<decltype(glGetActiveAttrib)*>(wglGetProcAddress("glGetActiveAttrib"));
		GetActiveSubroutineName = reinterpret_cast<decltype(glGetActiveSubroutineName)*>(wglGetProcAddress("glGetActiveSubroutineName"));
		GetActiveSubroutineUniformName = reinterpret_cast<decltype(glGetActiveSubroutineUniformName)*>(wglGetProcAddress("glGetActiveSubroutineUniformName"));
		GetActiveSubroutineUniformiv = reinterpret_cast<decltype(glGetActiveSubroutineUniformiv)*>(wglGetProcAddress("glGetActiveSubroutineUniformiv"));
		GetActiveUniform = reinterpret_cast<decltype(glGetActiveUniform)*>(wglGetProcAddress("glGetActiveUniform"));
		GetActiveUniformBlockName = reinterpret_cast<decltype(glGetActiveUniformBlockName)*>(wglGetProcAddress("glGetActiveUniformBlockName"));
		GetActiveUniformBlockiv = reinterpret_cast<decltype(glGetActiveUniformBlockiv)*>(wglGetProcAddress("glGetActiveUniformBlockiv"));
		GetActiveUniformName = reinterpret_cast<decltype(glGetActiveUniformName)*>(wglGetProcAddress("glGetActiveUniformName"));
		GetActiveUniformsiv = reinterpret_cast<decltype(glGetActiveUniformsiv)*>(wglGetProcAddress("glGetActiveUniformsiv"));
		GetAttachedShaders = reinterpret_cast<decltype(glGetAttachedShaders)*>(wglGetProcAddress("glGetAttachedShaders"));
		GetAttribLocation = reinterpret_cast<decltype(glGetAttribLocation)*>(wglGetProcAddress("glGetAttribLocation"));
		GetBooleani_v = reinterpret_cast<decltype(glGetBooleani_v)*>(wglGetProcAddress("glGetBooleani_v"));
		GetBufferParameteri64v = reinterpret_cast<decltype(glGetBufferParameteri64v)*>(wglGetProcAddress("glGetBufferParameteri64v"));
		GetBufferParameteriv = reinterpret_cast<decltype(glGetBufferParameteriv)*>(wglGetProcAddress("glGetBufferParameteriv"));
		GetBufferPointerv = reinterpret_cast<decltype(glGetBufferPointerv)*>(wglGetProcAddress("glGetBufferPointerv"));
		GetBufferSubData = reinterpret_cast<decltype(glGetBufferSubData)*>(wglGetProcAddress("glGetBufferSubData"));
		GetCompressedTexImage = reinterpret_cast<decltype(glGetCompressedTexImage)*>(wglGetProcAddress("glGetCompressedTexImage"));
		GetCompressedTextureImage = reinterpret_cast<decltype(glGetCompressedTextureImage)*>(wglGetProcAddress("glGetCompressedTextureImage"));
		GetCompressedTextureSubImage = reinterpret_cast<decltype(glGetCompressedTextureSubImage)*>(wglGetProcAddress("glGetCompressedTextureSubImage"));
		GetDebugMessageLog = reinterpret_cast<decltype(glGetDebugMessageLog)*>(wglGetProcAddress("glGetDebugMessageLog"));
		GetDoublei_v = reinterpret_cast<decltype(glGetDoublei_v)*>(wglGetProcAddress("glGetDoublei_v"));
		GetFloati_v = reinterpret_cast<decltype(glGetFloati_v)*>(wglGetProcAddress("glGetFloati_v"));
		GetFragDataIndex = reinterpret_cast<decltype(glGetFragDataIndex)*>(wglGetProcAddress("glGetFragDataIndex"));
		GetFragDataLocation = reinterpret_cast<decltype(glGetFragDataLocation)*>(wglGetProcAddress("glGetFragDataLocation"));
		GetFramebufferAttachmentParameteriv = reinterpret_cast<decltype(glGetFramebufferAttachmentParameteriv)*>(wglGetProcAddress("glGetFramebufferAttachmentParameteriv"));
		GetFramebufferParameteriv = reinterpret_cast<decltype(glGetFramebufferParameteriv)*>(wglGetProcAddress("glGetFramebufferParameteriv"));
		GetGraphicsResetStatus = reinterpret_cast<decltype(glGetGraphicsResetStatus)*>(wglGetProcAddress("glGetGraphicsResetStatus"));
		GetInteger64i_v = reinterpret_cast<decltype(glGetInteger64i_v)*>(wglGetProcAddress("glGetInteger64i_v"));
		GetInteger64v = reinterpret_cast<decltype(glGetInteger64v)*>(wglGetProcAddress("glGetInteger64v"));
		GetIntegeri_v = reinterpret_cast<decltype(glGetIntegeri_v)*>(wglGetProcAddress("glGetIntegeri_v"));
		GetInternalformati64v = reinterpret_cast<decltype(glGetInternalformati64v)*>(wglGetProcAddress("glGetInternalformati64v"));
		GetInternalformativ = reinterpret_cast<decltype(glGetInternalformativ)*>(wglGetProcAddress("glGetInternalformativ"));
		GetMultisamplefv = reinterpret_cast<decltype(glGetMultisamplefv)*>(wglGetProcAddress("glGetMultisamplefv"));
		GetNamedBufferParameteri64v = reinterpret_cast<decltype(glGetNamedBufferParameteri64v)*>(wglGetProcAddress("glGetNamedBufferParameteri64v"));
		GetNamedBufferParameteriv = reinterpret_cast<decltype(glGetNamedBufferParameteriv)*>(wglGetProcAddress("glGetNamedBufferParameteriv"));
		GetNamedBufferPointerv = reinterpret_cast<decltype(glGetNamedBufferPointerv)*>(wglGetProcAddress("glGetNamedBufferPointerv"));
		GetNamedBufferSubData = reinterpret_cast<decltype(glGetNamedBufferSubData)*>(wglGetProcAddress("glGetNamedBufferSubData"));
		GetNamedFramebufferAttachmentParameteriv = reinterpret_cast<decltype(glGetNamedFramebufferAttachmentParameteriv)*>(wglGetProcAddress("glGetNamedFramebufferAttachmentParameteriv"));
		GetNamedFramebufferParameteriv = reinterpret_cast<decltype(glGetNamedFramebufferParameteriv)*>(wglGetProcAddress("glGetNamedFramebufferParameteriv"));
		GetNamedRenderbufferParameteriv = reinterpret_cast<decltype(glGetNamedRenderbufferParameteriv)*>(wglGetProcAddress("glGetNamedRenderbufferParameteriv"));
		GetObjectLabel = reinterpret_cast<decltype(glGetObjectLabel)*>(wglGetProcAddress("glGetObjectLabel"));
		GetObjectPtrLabel = reinterpret_cast<decltype(glGetObjectPtrLabel)*>(wglGetProcAddress("glGetObjectPtrLabel"));
		GetProgramBinary = reinterpret_cast<decltype(glGetProgramBinary)*>(wglGetProcAddress("glGetProgramBinary"));
		GetProgramInfoLog = reinterpret_cast<decltype(glGetProgramInfoLog)*>(wglGetProcAddress("glGetProgramInfoLog"));
		GetProgramInterfaceiv = reinterpret_cast<decltype(glGetProgramInterfaceiv)*>(wglGetProcAddress("glGetProgramInterfaceiv"));
		GetProgramPipelineInfoLog = reinterpret_cast<decltype(glGetProgramPipelineInfoLog)*>(wglGetProcAddress("glGetProgramPipelineInfoLog"));
		GetProgramPipelineiv = reinterpret_cast<decltype(glGetProgramPipelineiv)*>(wglGetProcAddress("glGetProgramPipelineiv"));
		GetProgramResourceIndex = reinterpret_cast<decltype(glGetProgramResourceIndex)*>(wglGetProcAddress("glGetProgramResourceIndex"));
		GetProgramResourceLocation = reinterpret_cast<decltype(glGetProgramResourceLocation)*>(wglGetProcAddress("glGetProgramResourceLocation"));
		GetProgramResourceLocationIndex = reinterpret_cast<decltype(glGetProgramResourceLocationIndex)*>(wglGetProcAddress("glGetProgramResourceLocationIndex"));
		GetProgramResourceName = reinterpret_cast<decltype(glGetProgramResourceName)*>(wglGetProcAddress("glGetProgramResourceName"));
		GetProgramResourceiv = reinterpret_cast<decltype(glGetProgramResourceiv)*>(wglGetProcAddress("glGetProgramResourceiv"));
		GetProgramStageiv = reinterpret_cast<decltype(glGetProgramStageiv)*>(wglGetProcAddress("glGetProgramStageiv"));
		GetProgramiv = reinterpret_cast<decltype(glGetProgramiv)*>(wglGetProcAddress("glGetProgramiv"));
		GetQueryBufferObjecti64v = reinterpret_cast<decltype(glGetQueryBufferObjecti64v)*>(wglGetProcAddress("glGetQueryBufferObjecti64v"));
		GetQueryBufferObjectiv = reinterpret_cast<decltype(glGetQueryBufferObjectiv)*>(wglGetProcAddress("glGetQueryBufferObjectiv"));
		GetQueryBufferObjectui64v = reinterpret_cast<decltype(glGetQueryBufferObjectui64v)*>(wglGetProcAddress("glGetQueryBufferObjectui64v"));
		GetQueryBufferObjectuiv = reinterpret_cast<decltype(glGetQueryBufferObjectuiv)*>(wglGetProcAddress("glGetQueryBufferObjectuiv"));
		GetQueryIndexediv = reinterpret_cast<decltype(glGetQueryIndexediv)*>(wglGetProcAddress("glGetQueryIndexediv"));
		GetQueryObjecti64v = reinterpret_cast<decltype(glGetQueryObjecti64v)*>(wglGetProcAddress("glGetQueryObjecti64v"));
		GetQueryObjectiv = reinterpret_cast<decltype(glGetQueryObjectiv)*>(wglGetProcAddress("glGetQueryObjectiv"));
		GetQueryObjectui64v = reinterpret_cast<decltype(glGetQueryObjectui64v)*>(wglGetProcAddress("glGetQueryObjectui64v"));
		GetQueryObjectuiv = reinterpret_cast<decltype(glGetQueryObjectuiv)*>(wglGetProcAddress("glGetQueryObjectuiv"));
		GetQueryiv = reinterpret_cast<decltype(glGetQueryiv)*>(wglGetProcAddress("glGetQueryiv"));
		GetRenderbufferParameteriv = reinterpret_cast<decltype(glGetRenderbufferParameteriv)*>(wglGetProcAddress("glGetRenderbufferParameteriv"));
		GetSamplerParameterIiv = reinterpret_cast<decltype(glGetSamplerParameterIiv)*>(wglGetProcAddress("glGetSamplerParameterIiv"));
		GetSamplerParameterIuiv = reinterpret_cast<decltype(glGetSamplerParameterIuiv)*>(wglGetProcAddress("glGetSamplerParameterIuiv"));
		GetSamplerParameterfv = reinterpret_cast<decltype(glGetSamplerParameterfv)*>(wglGetProcAddress("glGetSamplerParameterfv"));
		GetSamplerParameteriv = reinterpret_cast<decltype(glGetSamplerParameteriv)*>(wglGetProcAddress("glGetSamplerParameteriv"));
		GetShaderInfoLog = reinterpret_cast<decltype(glGetShaderInfoLog)*>(wglGetProcAddress("glGetShaderInfoLog"));
		GetShaderPrecisionFormat = reinterpret_cast<decltype(glGetShaderPrecisionFormat)*>(wglGetProcAddress("glGetShaderPrecisionFormat"));
		GetShaderSource = reinterpret_cast<decltype(glGetShaderSource)*>(wglGetProcAddress("glGetShaderSource"));
		GetShaderiv = reinterpret_cast<decltype(glGetShaderiv)*>(wglGetProcAddress("glGetShaderiv"));
		GetStringi = reinterpret_cast<decltype(glGetStringi)*>(wglGetProcAddress("glGetStringi"));
		GetSubroutineIndex = reinterpret_cast<decltype(glGetSubroutineIndex)*>(wglGetProcAddress("glGetSubroutineIndex"));
		GetSubroutineUniformLocation = reinterpret_cast<decltype(glGetSubroutineUniformLocation)*>(wglGetProcAddress("glGetSubroutineUniformLocation"));
		GetSynciv = reinterpret_cast<decltype(glGetSynciv)*>(wglGetProcAddress("glGetSynciv"));
		GetTexParameterIiv = reinterpret_cast<decltype(glGetTexParameterIiv)*>(wglGetProcAddress("glGetTexParameterIiv"));
		GetTexParameterIuiv = reinterpret_cast<decltype(glGetTexParameterIuiv)*>(wglGetProcAddress("glGetTexParameterIuiv"));
		GetTextureImage = reinterpret_cast<decltype(glGetTextureImage)*>(wglGetProcAddress("glGetTextureImage"));
		GetTextureLevelParameterfv = reinterpret_cast<decltype(glGetTextureLevelParameterfv)*>(wglGetProcAddress("glGetTextureLevelParameterfv"));
		GetTextureLevelParameteriv = reinterpret_cast<decltype(glGetTextureLevelParameteriv)*>(wglGetProcAddress("glGetTextureLevelParameteriv"));
		GetTextureParameterIiv = reinterpret_cast<decltype(glGetTextureParameterIiv)*>(wglGetProcAddress("glGetTextureParameterIiv"));
		GetTextureParameterIuiv = reinterpret_cast<decltype(glGetTextureParameterIuiv)*>(wglGetProcAddress("glGetTextureParameterIuiv"));
		GetTextureParameterfv = reinterpret_cast<decltype(glGetTextureParameterfv)*>(wglGetProcAddress("glGetTextureParameterfv"));
		GetTextureParameteriv = reinterpret_cast<decltype(glGetTextureParameteriv)*>(wglGetProcAddress("glGetTextureParameteriv"));
		GetTextureSubImage = reinterpret_cast<decltype(glGetTextureSubImage)*>(wglGetProcAddress("glGetTextureSubImage"));
		GetTransformFeedbackVarying = reinterpret_cast<decltype(glGetTransformFeedbackVarying)*>(wglGetProcAddress("glGetTransformFeedbackVarying"));
		GetTransformFeedbacki64_v = reinterpret_cast<decltype(glGetTransformFeedbacki64_v)*>(wglGetProcAddress("glGetTransformFeedbacki64_v"));
		GetTransformFeedbacki_v = reinterpret_cast<decltype(glGetTransformFeedbacki_v)*>(wglGetProcAddress("glGetTransformFeedbacki_v"));
		GetTransformFeedbackiv = reinterpret_cast<decltype(glGetTransformFeedbackiv)*>(wglGetProcAddress("glGetTransformFeedbackiv"));
		GetUniformBlockIndex = reinterpret_cast<decltype(glGetUniformBlockIndex)*>(wglGetProcAddress("glGetUniformBlockIndex"));
		GetUniformIndices = reinterpret_cast<decltype(glGetUniformIndices)*>(wglGetProcAddress("glGetUniformIndices"));
		GetUniformLocation = reinterpret_cast<decltype(glGetUniformLocation)*>(wglGetProcAddress("glGetUniformLocation"));
		GetUniformSubroutineuiv = reinterpret_cast<decltype(glGetUniformSubroutineuiv)*>(wglGetProcAddress("glGetUniformSubroutineuiv"));
		GetUniformdv = reinterpret_cast<decltype(glGetUniformdv)*>(wglGetProcAddress("glGetUniformdv"));
		GetUniformfv = reinterpret_cast<decltype(glGetUniformfv)*>(wglGetProcAddress("glGetUniformfv"));
		GetUniformiv = reinterpret_cast<decltype(glGetUniformiv)*>(wglGetProcAddress("glGetUniformiv"));
		GetUniformuiv = reinterpret_cast<decltype(glGetUniformuiv)*>(wglGetProcAddress("glGetUniformuiv"));
		GetVertexArrayIndexed64iv = reinterpret_cast<decltype(glGetVertexArrayIndexed64iv)*>(wglGetProcAddress("glGetVertexArrayIndexed64iv"));
		GetVertexArrayIndexediv = reinterpret_cast<decltype(glGetVertexArrayIndexediv)*>(wglGetProcAddress("glGetVertexArrayIndexediv"));
		GetVertexArrayiv = reinterpret_cast<decltype(glGetVertexArrayiv)*>(wglGetProcAddress("glGetVertexArrayiv"));
		GetVertexAttribIiv = reinterpret_cast<decltype(glGetVertexAttribIiv)*>(wglGetProcAddress("glGetVertexAttribIiv"));
		GetVertexAttribIuiv = reinterpret_cast<decltype(glGetVertexAttribIuiv)*>(wglGetProcAddress("glGetVertexAttribIuiv"));
		GetVertexAttribLdv = reinterpret_cast<decltype(glGetVertexAttribLdv)*>(wglGetProcAddress("glGetVertexAttribLdv"));
		GetVertexAttribPointerv = reinterpret_cast<decltype(glGetVertexAttribPointerv)*>(wglGetProcAddress("glGetVertexAttribPointerv"));
		GetVertexAttribdv = reinterpret_cast<decltype(glGetVertexAttribdv)*>(wglGetProcAddress("glGetVertexAttribdv"));
		GetVertexAttribfv = reinterpret_cast<decltype(glGetVertexAttribfv)*>(wglGetProcAddress("glGetVertexAttribfv"));
		GetVertexAttribiv = reinterpret_cast<decltype(glGetVertexAttribiv)*>(wglGetProcAddress("glGetVertexAttribiv"));
		GetnCompressedTexImage = reinterpret_cast<decltype(glGetnCompressedTexImage)*>(wglGetProcAddress("glGetnCompressedTexImage"));
		GetnTexImage = reinterpret_cast<decltype(glGetnTexImage)*>(wglGetProcAddress("glGetnTexImage"));
		GetnUniformdv = reinterpret_cast<decltype(glGetnUniformdv)*>(wglGetProcAddress("glGetnUniformdv"));
		GetnUniformfv = reinterpret_cast<decltype(glGetnUniformfv)*>(wglGetProcAddress("glGetnUniformfv"));
		GetnUniformiv = reinterpret_cast<decltype(glGetnUniformiv)*>(wglGetProcAddress("glGetnUniformiv"));
		GetnUniformuiv = reinterpret_cast<decltype(glGetnUniformuiv)*>(wglGetProcAddress("glGetnUniformuiv"));
		InvalidateBufferData = reinterpret_cast<decltype(glInvalidateBufferData)*>(wglGetProcAddress("glInvalidateBufferData"));
		InvalidateBufferSubData = reinterpret_cast<decltype(glInvalidateBufferSubData)*>(wglGetProcAddress("glInvalidateBufferSubData"));
		InvalidateFramebuffer = reinterpret_cast<decltype(glInvalidateFramebuffer)*>(wglGetProcAddress("glInvalidateFramebuffer"));
		InvalidateNamedFramebufferData = reinterpret_cast<decltype(glInvalidateNamedFramebufferData)*>(wglGetProcAddress("glInvalidateNamedFramebufferData"));
		InvalidateNamedFramebufferSubData = reinterpret_cast<decltype(glInvalidateNamedFramebufferSubData)*>(wglGetProcAddress("glInvalidateNamedFramebufferSubData"));
		InvalidateSubFramebuffer = reinterpret_cast<decltype(glInvalidateSubFramebuffer)*>(wglGetProcAddress("glInvalidateSubFramebuffer"));
		InvalidateTexImage = reinterpret_cast<decltype(glInvalidateTexImage)*>(wglGetProcAddress("glInvalidateTexImage"));
		InvalidateTexSubImage = reinterpret_cast<decltype(glInvalidateTexSubImage)*>(wglGetProcAddress("glInvalidateTexSubImage"));
		IsBuffer = reinterpret_cast<decltype(glIsBuffer)*>(wglGetProcAddress("glIsBuffer"));
		IsEnabledi = reinterpret_cast<decltype(glIsEnabledi)*>(wglGetProcAddress("glIsEnabledi"));
		IsFramebuffer = reinterpret_cast<decltype(glIsFramebuffer)*>(wglGetProcAddress("glIsFramebuffer"));
		IsProgram = reinterpret_cast<decltype(glIsProgram)*>(wglGetProcAddress("glIsProgram"));
		IsProgramPipeline = reinterpret_cast<decltype(glIsProgramPipeline)*>(wglGetProcAddress("glIsProgramPipeline"));
		IsQuery = reinterpret_cast<decltype(glIsQuery)*>(wglGetProcAddress("glIsQuery"));
		IsRenderbuffer = reinterpret_cast<decltype(glIsRenderbuffer)*>(wglGetProcAddress("glIsRenderbuffer"));
		IsSampler = reinterpret_cast<decltype(glIsSampler)*>(wglGetProcAddress("glIsSampler"));
		IsShader = reinterpret_cast<decltype(glIsShader)*>(wglGetProcAddress("glIsShader"));
		IsSync = reinterpret_cast<decltype(glIsSync)*>(wglGetProcAddress("glIsSync"));
		IsTransformFeedback = reinterpret_cast<decltype(glIsTransformFeedback)*>(wglGetProcAddress("glIsTransformFeedback"));
		IsVertexArray = reinterpret_cast<decltype(glIsVertexArray)*>(wglGetProcAddress("glIsVertexArray"));
		LinkProgram = reinterpret_cast<decltype(glLinkProgram)*>(wglGetProcAddress("glLinkProgram"));
		MapBuffer = reinterpret_cast<decltype(glMapBuffer)*>(wglGetProcAddress("glMapBuffer"));
		MapBufferRange = reinterpret_cast<decltype(glMapBufferRange)*>(wglGetProcAddress("glMapBufferRange"));
		MapNamedBuffer = reinterpret_cast<decltype(glMapNamedBuffer)*>(wglGetProcAddress("glMapNamedBuffer"));
		MapNamedBufferRange = reinterpret_cast<decltype(glMapNamedBufferRange)*>(wglGetProcAddress("glMapNamedBufferRange"));
		MemoryBarrier = reinterpret_cast<decltype(glMemoryBarrier)*>(wglGetProcAddress("glMemoryBarrier"));
		MemoryBarrierByRegion = reinterpret_cast<decltype(glMemoryBarrierByRegion)*>(wglGetProcAddress("glMemoryBarrierByRegion"));
		MinSampleShading = reinterpret_cast<decltype(glMinSampleShading)*>(wglGetProcAddress("glMinSampleShading"));
		MultiDrawArrays = reinterpret_cast<decltype(glMultiDrawArrays)*>(wglGetProcAddress("glMultiDrawArrays"));
		MultiDrawArraysIndirect = reinterpret_cast<decltype(glMultiDrawArraysIndirect)*>(wglGetProcAddress("glMultiDrawArraysIndirect"));
		MultiDrawElements = reinterpret_cast<decltype(glMultiDrawElements)*>(wglGetProcAddress("glMultiDrawElements"));
		MultiDrawElementsBaseVertex = reinterpret_cast<decltype(glMultiDrawElementsBaseVertex)*>(wglGetProcAddress("glMultiDrawElementsBaseVertex"));
		MultiDrawElementsIndirect = reinterpret_cast<decltype(glMultiDrawElementsIndirect)*>(wglGetProcAddress("glMultiDrawElementsIndirect"));
		NamedBufferData = reinterpret_cast<decltype(glNamedBufferData)*>(wglGetProcAddress("glNamedBufferData"));
		NamedBufferStorage = reinterpret_cast<decltype(glNamedBufferStorage)*>(wglGetProcAddress("glNamedBufferStorage"));
		NamedBufferSubData = reinterpret_cast<decltype(glNamedBufferSubData)*>(wglGetProcAddress("glNamedBufferSubData"));
		NamedFramebufferDrawBuffer = reinterpret_cast<decltype(glNamedFramebufferDrawBuffer)*>(wglGetProcAddress("glNamedFramebufferDrawBuffer"));
		NamedFramebufferDrawBuffers = reinterpret_cast<decltype(glNamedFramebufferDrawBuffers)*>(wglGetProcAddress("glNamedFramebufferDrawBuffers"));
		NamedFramebufferParameteri = reinterpret_cast<decltype(glNamedFramebufferParameteri)*>(wglGetProcAddress("glNamedFramebufferParameteri"));
		NamedFramebufferReadBuffer = reinterpret_cast<decltype(glNamedFramebufferReadBuffer)*>(wglGetProcAddress("glNamedFramebufferReadBuffer"));
		NamedFramebufferRenderbuffer = reinterpret_cast<decltype(glNamedFramebufferRenderbuffer)*>(wglGetProcAddress("glNamedFramebufferRenderbuffer"));
		NamedFramebufferTexture = reinterpret_cast<decltype(glNamedFramebufferTexture)*>(wglGetProcAddress("glNamedFramebufferTexture"));
		NamedFramebufferTextureLayer = reinterpret_cast<decltype(glNamedFramebufferTextureLayer)*>(wglGetProcAddress("glNamedFramebufferTextureLayer"));
		NamedRenderbufferStorage = reinterpret_cast<decltype(glNamedRenderbufferStorage)*>(wglGetProcAddress("glNamedRenderbufferStorage"));
		NamedRenderbufferStorageMultisample = reinterpret_cast<decltype(glNamedRenderbufferStorageMultisample)*>(wglGetProcAddress("glNamedRenderbufferStorageMultisample"));
		ObjectLabel = reinterpret_cast<decltype(glObjectLabel)*>(wglGetProcAddress("glObjectLabel"));
		ObjectPtrLabel = reinterpret_cast<decltype(glObjectPtrLabel)*>(wglGetProcAddress("glObjectPtrLabel"));
		PatchParameterfv = reinterpret_cast<decltype(glPatchParameterfv)*>(wglGetProcAddress("glPatchParameterfv"));
		PatchParameteri = reinterpret_cast<decltype(glPatchParameteri)*>(wglGetProcAddress("glPatchParameteri"));
		PauseTransformFeedback = reinterpret_cast<decltype(glPauseTransformFeedback)*>(wglGetProcAddress("glPauseTransformFeedback"));
		PointParameterf = reinterpret_cast<decltype(glPointParameterf)*>(wglGetProcAddress("glPointParameterf"));
		PointParameterfv = reinterpret_cast<decltype(glPointParameterfv)*>(wglGetProcAddress("glPointParameterfv"));
		PointParameteri = reinterpret_cast<decltype(glPointParameteri)*>(wglGetProcAddress("glPointParameteri"));
		PointParameteriv = reinterpret_cast<decltype(glPointParameteriv)*>(wglGetProcAddress("glPointParameteriv"));
		PopDebugGroup = reinterpret_cast<decltype(glPopDebugGroup)*>(wglGetProcAddress("glPopDebugGroup"));
		PrimitiveRestartIndex = reinterpret_cast<decltype(glPrimitiveRestartIndex)*>(wglGetProcAddress("glPrimitiveRestartIndex"));
		ProgramBinary = reinterpret_cast<decltype(glProgramBinary)*>(wglGetProcAddress("glProgramBinary"));
		ProgramParameteri = reinterpret_cast<decltype(glProgramParameteri)*>(wglGetProcAddress("glProgramParameteri"));
		ProgramUniform1d = reinterpret_cast<decltype(glProgramUniform1d)*>(wglGetProcAddress("glProgramUniform1d"));
		ProgramUniform1dv = reinterpret_cast<decltype(glProgramUniform1dv)*>(wglGetProcAddress("glProgramUniform1dv"));
		ProgramUniform1f = reinterpret_cast<decltype(glProgramUniform1f)*>(wglGetProcAddress("glProgramUniform1f"));
		ProgramUniform1fv = reinterpret_cast<decltype(glProgramUniform1fv)*>(wglGetProcAddress("glProgramUniform1fv"));
		ProgramUniform1i = reinterpret_cast<decltype(glProgramUniform1i)*>(wglGetProcAddress("glProgramUniform1i"));
		ProgramUniform1iv = reinterpret_cast<decltype(glProgramUniform1iv)*>(wglGetProcAddress("glProgramUniform1iv"));
		ProgramUniform1ui = reinterpret_cast<decltype(glProgramUniform1ui)*>(wglGetProcAddress("glProgramUniform1ui"));
		ProgramUniform1uiv = reinterpret_cast<decltype(glProgramUniform1uiv)*>(wglGetProcAddress("glProgramUniform1uiv"));
		ProgramUniform2d = reinterpret_cast<decltype(glProgramUniform2d)*>(wglGetProcAddress("glProgramUniform2d"));
		ProgramUniform2dv = reinterpret_cast<decltype(glProgramUniform2dv)*>(wglGetProcAddress("glProgramUniform2dv"));
		ProgramUniform2f = reinterpret_cast<decltype(glProgramUniform2f)*>(wglGetProcAddress("glProgramUniform2f"));
		ProgramUniform2fv = reinterpret_cast<decltype(glProgramUniform2fv)*>(wglGetProcAddress("glProgramUniform2fv"));
		ProgramUniform2i = reinterpret_cast<decltype(glProgramUniform2i)*>(wglGetProcAddress("glProgramUniform2i"));
		ProgramUniform2iv = reinterpret_cast<decltype(glProgramUniform2iv)*>(wglGetProcAddress("glProgramUniform2iv"));
		ProgramUniform2ui = reinterpret_cast<decltype(glProgramUniform2ui)*>(wglGetProcAddress("glProgramUniform2ui"));
		ProgramUniform2uiv = reinterpret_cast<decltype(glProgramUniform2uiv)*>(wglGetProcAddress("glProgramUniform2uiv"));
		ProgramUniform3d = reinterpret_cast<decltype(glProgramUniform3d)*>(wglGetProcAddress("glProgramUniform3d"));
		ProgramUniform3dv = reinterpret_cast<decltype(glProgramUniform3dv)*>(wglGetProcAddress("glProgramUniform3dv"));
		ProgramUniform3f = reinterpret_cast<decltype(glProgramUniform3f)*>(wglGetProcAddress("glProgramUniform3f"));
		ProgramUniform3fv = reinterpret_cast<decltype(glProgramUniform3fv)*>(wglGetProcAddress("glProgramUniform3fv"));
		ProgramUniform3i = reinterpret_cast<decltype(glProgramUniform3i)*>(wglGetProcAddress("glProgramUniform3i"));
		ProgramUniform3iv = reinterpret_cast<decltype(glProgramUniform3iv)*>(wglGetProcAddress("glProgramUniform3iv"));
		ProgramUniform3ui = reinterpret_cast<decltype(glProgramUniform3ui)*>(wglGetProcAddress("glProgramUniform3ui"));
		ProgramUniform3uiv = reinterpret_cast<decltype(glProgramUniform3uiv)*>(wglGetProcAddress("glProgramUniform3uiv"));
		ProgramUniform4d = reinterpret_cast<decltype(glProgramUniform4d)*>(wglGetProcAddress("glProgramUniform4d"));
		ProgramUniform4dv = reinterpret_cast<decltype(glProgramUniform4dv)*>(wglGetProcAddress("glProgramUniform4dv"));
		ProgramUniform4f = reinterpret_cast<decltype(glProgramUniform4f)*>(wglGetProcAddress("glProgramUniform4f"));
		ProgramUniform4fv = reinterpret_cast<decltype(glProgramUniform4fv)*>(wglGetProcAddress("glProgramUniform4fv"));
		ProgramUniform4i = reinterpret_cast<decltype(glProgramUniform4i)*>(wglGetProcAddress("glProgramUniform4i"));
		ProgramUniform4iv = reinterpret_cast<decltype(glProgramUniform4iv)*>(wglGetProcAddress("glProgramUniform4iv"));
		ProgramUniform4ui = reinterpret_cast<decltype(glProgramUniform4ui)*>(wglGetProcAddress("glProgramUniform4ui"));
		ProgramUniform4uiv = reinterpret_cast<decltype(glProgramUniform4uiv)*>(wglGetProcAddress("glProgramUniform4uiv"));
		ProgramUniformMatrix2dv = reinterpret_cast<decltype(glProgramUniformMatrix2dv)*>(wglGetProcAddress("glProgramUniformMatrix2dv"));
		ProgramUniformMatrix2fv = reinterpret_cast<decltype(glProgramUniformMatrix2fv)*>(wglGetProcAddress("glProgramUniformMatrix2fv"));
		ProgramUniformMatrix2x3dv = reinterpret_cast<decltype(glProgramUniformMatrix2x3dv)*>(wglGetProcAddress("glProgramUniformMatrix2x3dv"));
		ProgramUniformMatrix2x3fv = reinterpret_cast<decltype(glProgramUniformMatrix2x3fv)*>(wglGetProcAddress("glProgramUniformMatrix2x3fv"));
		ProgramUniformMatrix2x4dv = reinterpret_cast<decltype(glProgramUniformMatrix2x4dv)*>(wglGetProcAddress("glProgramUniformMatrix2x4dv"));
		ProgramUniformMatrix2x4fv = reinterpret_cast<decltype(glProgramUniformMatrix2x4fv)*>(wglGetProcAddress("glProgramUniformMatrix2x4fv"));
		ProgramUniformMatrix3dv = reinterpret_cast<decltype(glProgramUniformMatrix3dv)*>(wglGetProcAddress("glProgramUniformMatrix3dv"));
		ProgramUniformMatrix3fv = reinterpret_cast<decltype(glProgramUniformMatrix3fv)*>(wglGetProcAddress("glProgramUniformMatrix3fv"));
		ProgramUniformMatrix3x2dv = reinterpret_cast<decltype(glProgramUniformMatrix3x2dv)*>(wglGetProcAddress("glProgramUniformMatrix3x2dv"));
		ProgramUniformMatrix3x2fv = reinterpret_cast<decltype(glProgramUniformMatrix3x2fv)*>(wglGetProcAddress("glProgramUniformMatrix3x2fv"));
		ProgramUniformMatrix3x4dv = reinterpret_cast<decltype(glProgramUniformMatrix3x4dv)*>(wglGetProcAddress("glProgramUniformMatrix3x4dv"));
		ProgramUniformMatrix3x4fv = reinterpret_cast<decltype(glProgramUniformMatrix3x4fv)*>(wglGetProcAddress("glProgramUniformMatrix3x4fv"));
		ProgramUniformMatrix4dv = reinterpret_cast<decltype(glProgramUniformMatrix4dv)*>(wglGetProcAddress("glProgramUniformMatrix4dv"));
		ProgramUniformMatrix4fv = reinterpret_cast<decltype(glProgramUniformMatrix4fv)*>(wglGetProcAddress("glProgramUniformMatrix4fv"));
		ProgramUniformMatrix4x2dv = reinterpret_cast<decltype(glProgramUniformMatrix4x2dv)*>(wglGetProcAddress("glProgramUniformMatrix4x2dv"));
		ProgramUniformMatrix4x2fv = reinterpret_cast<decltype(glProgramUniformMatrix4x2fv)*>(wglGetProcAddress("glProgramUniformMatrix4x2fv"));
		ProgramUniformMatrix4x3dv = reinterpret_cast<decltype(glProgramUniformMatrix4x3dv)*>(wglGetProcAddress("glProgramUniformMatrix4x3dv"));
		ProgramUniformMatrix4x3fv = reinterpret_cast<decltype(glProgramUniformMatrix4x3fv)*>(wglGetProcAddress("glProgramUniformMatrix4x3fv"));
		ProvokingVertex = reinterpret_cast<decltype(glProvokingVertex)*>(wglGetProcAddress("glProvokingVertex"));
		PushDebugGroup = reinterpret_cast<decltype(glPushDebugGroup)*>(wglGetProcAddress("glPushDebugGroup"));
		QueryCounter = reinterpret_cast<decltype(glQueryCounter)*>(wglGetProcAddress("glQueryCounter"));
		ReadnPixels = reinterpret_cast<decltype(glReadnPixels)*>(wglGetProcAddress("glReadnPixels"));
		ReleaseShaderCompiler = reinterpret_cast<decltype(glReleaseShaderCompiler)*>(wglGetProcAddress("glReleaseShaderCompiler"));
		RenderbufferStorage = reinterpret_cast<decltype(glRenderbufferStorage)*>(wglGetProcAddress("glRenderbufferStorage"));
		RenderbufferStorageMultisample = reinterpret_cast<decltype(glRenderbufferStorageMultisample)*>(wglGetProcAddress("glRenderbufferStorageMultisample"));
		ResumeTransformFeedback = reinterpret_cast<decltype(glResumeTransformFeedback)*>(wglGetProcAddress("glResumeTransformFeedback"));
		SampleCoverage = reinterpret_cast<decltype(glSampleCoverage)*>(wglGetProcAddress("glSampleCoverage"));
		SampleMaski = reinterpret_cast<decltype(glSampleMaski)*>(wglGetProcAddress("glSampleMaski"));
		SamplerParameterIiv = reinterpret_cast<decltype(glSamplerParameterIiv)*>(wglGetProcAddress("glSamplerParameterIiv"));
		SamplerParameterIuiv = reinterpret_cast<decltype(glSamplerParameterIuiv)*>(wglGetProcAddress("glSamplerParameterIuiv"));
		SamplerParameterf = reinterpret_cast<decltype(glSamplerParameterf)*>(wglGetProcAddress("glSamplerParameterf"));
		SamplerParameterfv = reinterpret_cast<decltype(glSamplerParameterfv)*>(wglGetProcAddress("glSamplerParameterfv"));
		SamplerParameteri = reinterpret_cast<decltype(glSamplerParameteri)*>(wglGetProcAddress("glSamplerParameteri"));
		SamplerParameteriv = reinterpret_cast<decltype(glSamplerParameteriv)*>(wglGetProcAddress("glSamplerParameteriv"));
		ScissorArrayv = reinterpret_cast<decltype(glScissorArrayv)*>(wglGetProcAddress("glScissorArrayv"));
		ScissorIndexed = reinterpret_cast<decltype(glScissorIndexed)*>(wglGetProcAddress("glScissorIndexed"));
		ScissorIndexedv = reinterpret_cast<decltype(glScissorIndexedv)*>(wglGetProcAddress("glScissorIndexedv"));
		ShaderBinary = reinterpret_cast<decltype(glShaderBinary)*>(wglGetProcAddress("glShaderBinary"));
		ShaderSource = reinterpret_cast<decltype(glShaderSource)*>(wglGetProcAddress("glShaderSource"));
		ShaderStorageBlockBinding = reinterpret_cast<decltype(glShaderStorageBlockBinding)*>(wglGetProcAddress("glShaderStorageBlockBinding"));
		StencilFuncSeparate = reinterpret_cast<decltype(glStencilFuncSeparate)*>(wglGetProcAddress("glStencilFuncSeparate"));
		StencilMaskSeparate = reinterpret_cast<decltype(glStencilMaskSeparate)*>(wglGetProcAddress("glStencilMaskSeparate"));
		StencilOpSeparate = reinterpret_cast<decltype(glStencilOpSeparate)*>(wglGetProcAddress("glStencilOpSeparate"));
		TexBuffer = reinterpret_cast<decltype(glTexBuffer)*>(wglGetProcAddress("glTexBuffer"));
		TexBufferRange = reinterpret_cast<decltype(glTexBufferRange)*>(wglGetProcAddress("glTexBufferRange"));
		TexImage2DMultisample = reinterpret_cast<decltype(glTexImage2DMultisample)*>(wglGetProcAddress("glTexImage2DMultisample"));
		TexImage3D = reinterpret_cast<decltype(glTexImage3D)*>(wglGetProcAddress("glTexImage3D"));
		TexImage3DMultisample = reinterpret_cast<decltype(glTexImage3DMultisample)*>(wglGetProcAddress("glTexImage3DMultisample"));
		TexParameterIiv = reinterpret_cast<decltype(glTexParameterIiv)*>(wglGetProcAddress("glTexParameterIiv"));
		TexParameterIuiv = reinterpret_cast<decltype(glTexParameterIuiv)*>(wglGetProcAddress("glTexParameterIuiv"));
		TexStorage1D = reinterpret_cast<decltype(glTexStorage1D)*>(wglGetProcAddress("glTexStorage1D"));
		TexStorage2D = reinterpret_cast<decltype(glTexStorage2D)*>(wglGetProcAddress("glTexStorage2D"));
		TexStorage2DMultisample = reinterpret_cast<decltype(glTexStorage2DMultisample)*>(wglGetProcAddress("glTexStorage2DMultisample"));
		TexStorage3D = reinterpret_cast<decltype(glTexStorage3D)*>(wglGetProcAddress("glTexStorage3D"));
		TexStorage3DMultisample = reinterpret_cast<decltype(glTexStorage3DMultisample)*>(wglGetProcAddress("glTexStorage3DMultisample"));
		TexSubImage3D = reinterpret_cast<decltype(glTexSubImage3D)*>(wglGetProcAddress("glTexSubImage3D"));
		TextureBarrier = reinterpret_cast<decltype(glTextureBarrier)*>(wglGetProcAddress("glTextureBarrier"));
		TextureBuffer = reinterpret_cast<decltype(glTextureBuffer)*>(wglGetProcAddress("glTextureBuffer"));
		TextureBufferRange = reinterpret_cast<decltype(glTextureBufferRange)*>(wglGetProcAddress("glTextureBufferRange"));
		TextureParameterIiv = reinterpret_cast<decltype(glTextureParameterIiv)*>(wglGetProcAddress("glTextureParameterIiv"));
		TextureParameterIuiv = reinterpret_cast<decltype(glTextureParameterIuiv)*>(wglGetProcAddress("glTextureParameterIuiv"));
		TextureParameterf = reinterpret_cast<decltype(glTextureParameterf)*>(wglGetProcAddress("glTextureParameterf"));
		TextureParameterfv = reinterpret_cast<decltype(glTextureParameterfv)*>(wglGetProcAddress("glTextureParameterfv"));
		TextureParameteri = reinterpret_cast<decltype(glTextureParameteri)*>(wglGetProcAddress("glTextureParameteri"));
		TextureParameteriv = reinterpret_cast<decltype(glTextureParameteriv)*>(wglGetProcAddress("glTextureParameteriv"));
		TextureStorage1D = reinterpret_cast<decltype(glTextureStorage1D)*>(wglGetProcAddress("glTextureStorage1D"));
		TextureStorage2D = reinterpret_cast<decltype(glTextureStorage2D)*>(wglGetProcAddress("glTextureStorage2D"));
		TextureStorage2DMultisample = reinterpret_cast<decltype(glTextureStorage2DMultisample)*>(wglGetProcAddress("glTextureStorage2DMultisample"));
		TextureStorage3D = reinterpret_cast<decltype(glTextureStorage3D)*>(wglGetProcAddress("glTextureStorage3D"));
		TextureStorage3DMultisample = reinterpret_cast<decltype(glTextureStorage3DMultisample)*>(wglGetProcAddress("glTextureStorage3DMultisample"));
		TextureSubImage1D = reinterpret_cast<decltype(glTextureSubImage1D)*>(wglGetProcAddress("glTextureSubImage1D"));
		TextureSubImage2D = reinterpret_cast<decltype(glTextureSubImage2D)*>(wglGetProcAddress("glTextureSubImage2D"));
		TextureSubImage3D = reinterpret_cast<decltype(glTextureSubImage3D)*>(wglGetProcAddress("glTextureSubImage3D"));
		TextureView = reinterpret_cast<decltype(glTextureView)*>(wglGetProcAddress("glTextureView"));
		TransformFeedbackBufferBase = reinterpret_cast<decltype(glTransformFeedbackBufferBase)*>(wglGetProcAddress("glTransformFeedbackBufferBase"));
		TransformFeedbackBufferRange = reinterpret_cast<decltype(glTransformFeedbackBufferRange)*>(wglGetProcAddress("glTransformFeedbackBufferRange"));
		TransformFeedbackVaryings = reinterpret_cast<decltype(glTransformFeedbackVaryings)*>(wglGetProcAddress("glTransformFeedbackVaryings"));
		Uniform1d = reinterpret_cast<decltype(glUniform1d)*>(wglGetProcAddress("glUniform1d"));
		Uniform1dv = reinterpret_cast<decltype(glUniform1dv)*>(wglGetProcAddress("glUniform1dv"));
		Uniform1f = reinterpret_cast<decltype(glUniform1f)*>(wglGetProcAddress("glUniform1f"));
		Uniform1fv = reinterpret_cast<decltype(glUniform1fv)*>(wglGetProcAddress("glUniform1fv"));
		Uniform1i = reinterpret_cast<decltype(glUniform1i)*>(wglGetProcAddress("glUniform1i"));
		Uniform1iv = reinterpret_cast<decltype(glUniform1iv)*>(wglGetProcAddress("glUniform1iv"));
		Uniform1ui = reinterpret_cast<decltype(glUniform1ui)*>(wglGetProcAddress("glUniform1ui"));
		Uniform1uiv = reinterpret_cast<decltype(glUniform1uiv)*>(wglGetProcAddress("glUniform1uiv"));
		Uniform2d = reinterpret_cast<decltype(glUniform2d)*>(wglGetProcAddress("glUniform2d"));
		Uniform2dv = reinterpret_cast<decltype(glUniform2dv)*>(wglGetProcAddress("glUniform2dv"));
		Uniform2f = reinterpret_cast<decltype(glUniform2f)*>(wglGetProcAddress("glUniform2f"));
		Uniform2fv = reinterpret_cast<decltype(glUniform2fv)*>(wglGetProcAddress("glUniform2fv"));
		Uniform2i = reinterpret_cast<decltype(glUniform2i)*>(wglGetProcAddress("glUniform2i"));
		Uniform2iv = reinterpret_cast<decltype(glUniform2iv)*>(wglGetProcAddress("glUniform2iv"));
		Uniform2ui = reinterpret_cast<decltype(glUniform2ui)*>(wglGetProcAddress("glUniform2ui"));
		Uniform2uiv = reinterpret_cast<decltype(glUniform2uiv)*>(wglGetProcAddress("glUniform2uiv"));
		Uniform3d = reinterpret_cast<decltype(glUniform3d)*>(wglGetProcAddress("glUniform3d"));
		Uniform3dv = reinterpret_cast<decltype(glUniform3dv)*>(wglGetProcAddress("glUniform3dv"));
		Uniform3f = reinterpret_cast<decltype(glUniform3f)*>(wglGetProcAddress("glUniform3f"));
		Uniform3fv = reinterpret_cast<decltype(glUniform3fv)*>(wglGetProcAddress("glUniform3fv"));
		Uniform3i = reinterpret_cast<decltype(glUniform3i)*>(wglGetProcAddress("glUniform3i"));
		Uniform3iv = reinterpret_cast<decltype(glUniform3iv)*>(wglGetProcAddress("glUniform3iv"));
		Uniform3ui = reinterpret_cast<decltype(glUniform3ui)*>(wglGetProcAddress("glUniform3ui"));
		Uniform3uiv = reinterpret_cast<decltype(glUniform3uiv)*>(wglGetProcAddress("glUniform3uiv"));
		Uniform4d = reinterpret_cast<decltype(glUniform4d)*>(wglGetProcAddress("glUniform4d"));
		Uniform4dv = reinterpret_cast<decltype(glUniform4dv)*>(wglGetProcAddress("glUniform4dv"));
		Uniform4f = reinterpret_cast<decltype(glUniform4f)*>(wglGetProcAddress("glUniform4f"));
		Uniform4fv = reinterpret_cast<decltype(glUniform4fv)*>(wglGetProcAddress("glUniform4fv"));
		Uniform4i = reinterpret_cast<decltype(glUniform4i)*>(wglGetProcAddress("glUniform4i"));
		Uniform4iv = reinterpret_cast<decltype(glUniform4iv)*>(wglGetProcAddress("glUniform4iv"));
		Uniform4ui = reinterpret_cast<decltype(glUniform4ui)*>(wglGetProcAddress("glUniform4ui"));
		Uniform4uiv = reinterpret_cast<decltype(glUniform4uiv)*>(wglGetProcAddress("glUniform4uiv"));
		UniformBlockBinding = reinterpret_cast<decltype(glUniformBlockBinding)*>(wglGetProcAddress("glUniformBlockBinding"));
		UniformMatrix2dv = reinterpret_cast<decltype(glUniformMatrix2dv)*>(wglGetProcAddress("glUniformMatrix2dv"));
		UniformMatrix2fv = reinterpret_cast<decltype(glUniformMatrix2fv)*>(wglGetProcAddress("glUniformMatrix2fv"));
		UniformMatrix2x3dv = reinterpret_cast<decltype(glUniformMatrix2x3dv)*>(wglGetProcAddress("glUniformMatrix2x3dv"));
		UniformMatrix2x3fv = reinterpret_cast<decltype(glUniformMatrix2x3fv)*>(wglGetProcAddress("glUniformMatrix2x3fv"));
		UniformMatrix2x4dv = reinterpret_cast<decltype(glUniformMatrix2x4dv)*>(wglGetProcAddress("glUniformMatrix2x4dv"));
		UniformMatrix2x4fv = reinterpret_cast<decltype(glUniformMatrix2x4fv)*>(wglGetProcAddress("glUniformMatrix2x4fv"));
		UniformMatrix3dv = reinterpret_cast<decltype(glUniformMatrix3dv)*>(wglGetProcAddress("glUniformMatrix3dv"));
		UniformMatrix3fv = reinterpret_cast<decltype(glUniformMatrix3fv)*>(wglGetProcAddress("glUniformMatrix3fv"));
		UniformMatrix3x2dv = reinterpret_cast<decltype(glUniformMatrix3x2dv)*>(wglGetProcAddress("glUniformMatrix3x2dv"));
		UniformMatrix3x2fv = reinterpret_cast<decltype(glUniformMatrix3x2fv)*>(wglGetProcAddress("glUniformMatrix3x2fv"));
		UniformMatrix3x4dv = reinterpret_cast<decltype(glUniformMatrix3x4dv)*>(wglGetProcAddress("glUniformMatrix3x4dv"));
		UniformMatrix3x4fv = reinterpret_cast<decltype(glUniformMatrix3x4fv)*>(wglGetProcAddress("glUniformMatrix3x4fv"));
		UniformMatrix4dv = reinterpret_cast<decltype(glUniformMatrix4dv)*>(wglGetProcAddress("glUniformMatrix4dv"));
		UniformMatrix4fv = reinterpret_cast<decltype(glUniformMatrix4fv)*>(wglGetProcAddress("glUniformMatrix4fv"));
		UniformMatrix4x2dv = reinterpret_cast<decltype(glUniformMatrix4x2dv)*>(wglGetProcAddress("glUniformMatrix4x2dv"));
		UniformMatrix4x2fv = reinterpret_cast<decltype(glUniformMatrix4x2fv)*>(wglGetProcAddress("glUniformMatrix4x2fv"));
		UniformMatrix4x3dv = reinterpret_cast<decltype(glUniformMatrix4x3dv)*>(wglGetProcAddress("glUniformMatrix4x3dv"));
		UniformMatrix4x3fv = reinterpret_cast<decltype(glUniformMatrix4x3fv)*>(wglGetProcAddress("glUniformMatrix4x3fv"));
		UniformSubroutinesuiv = reinterpret_cast<decltype(glUniformSubroutinesuiv)*>(wglGetProcAddress("glUniformSubroutinesuiv"));
		UnmapBuffer = reinterpret_cast<decltype(glUnmapBuffer)*>(wglGetProcAddress("glUnmapBuffer"));
		UnmapNamedBuffer = reinterpret_cast<decltype(glUnmapNamedBuffer)*>(wglGetProcAddress("glUnmapNamedBuffer"));
		UseProgram = reinterpret_cast<decltype(glUseProgram)*>(wglGetProcAddress("glUseProgram"));
		UseProgramStages = reinterpret_cast<decltype(glUseProgramStages)*>(wglGetProcAddress("glUseProgramStages"));
		ValidateProgram = reinterpret_cast<decltype(glValidateProgram)*>(wglGetProcAddress("glValidateProgram"));
		ValidateProgramPipeline = reinterpret_cast<decltype(glValidateProgramPipeline)*>(wglGetProcAddress("glValidateProgramPipeline"));
		VertexArrayAttribBinding = reinterpret_cast<decltype(glVertexArrayAttribBinding)*>(wglGetProcAddress("glVertexArrayAttribBinding"));
		VertexArrayAttribFormat = reinterpret_cast<decltype(glVertexArrayAttribFormat)*>(wglGetProcAddress("glVertexArrayAttribFormat"));
		VertexArrayAttribIFormat = reinterpret_cast<decltype(glVertexArrayAttribIFormat)*>(wglGetProcAddress("glVertexArrayAttribIFormat"));
		VertexArrayAttribLFormat = reinterpret_cast<decltype(glVertexArrayAttribLFormat)*>(wglGetProcAddress("glVertexArrayAttribLFormat"));
		VertexArrayBindingDivisor = reinterpret_cast<decltype(glVertexArrayBindingDivisor)*>(wglGetProcAddress("glVertexArrayBindingDivisor"));
		VertexArrayElementBuffer = reinterpret_cast<decltype(glVertexArrayElementBuffer)*>(wglGetProcAddress("glVertexArrayElementBuffer"));
		VertexArrayVertexBuffer = reinterpret_cast<decltype(glVertexArrayVertexBuffer)*>(wglGetProcAddress("glVertexArrayVertexBuffer"));
		VertexArrayVertexBuffers = reinterpret_cast<decltype(glVertexArrayVertexBuffers)*>(wglGetProcAddress("glVertexArrayVertexBuffers"));
		VertexAttrib1d = reinterpret_cast<decltype(glVertexAttrib1d)*>(wglGetProcAddress("glVertexAttrib1d"));
		VertexAttrib1dv = reinterpret_cast<decltype(glVertexAttrib1dv)*>(wglGetProcAddress("glVertexAttrib1dv"));
		VertexAttrib1f = reinterpret_cast<decltype(glVertexAttrib1f)*>(wglGetProcAddress("glVertexAttrib1f"));
		VertexAttrib1fv = reinterpret_cast<decltype(glVertexAttrib1fv)*>(wglGetProcAddress("glVertexAttrib1fv"));
		VertexAttrib1s = reinterpret_cast<decltype(glVertexAttrib1s)*>(wglGetProcAddress("glVertexAttrib1s"));
		VertexAttrib1sv = reinterpret_cast<decltype(glVertexAttrib1sv)*>(wglGetProcAddress("glVertexAttrib1sv"));
		VertexAttrib2d = reinterpret_cast<decltype(glVertexAttrib2d)*>(wglGetProcAddress("glVertexAttrib2d"));
		VertexAttrib2dv = reinterpret_cast<decltype(glVertexAttrib2dv)*>(wglGetProcAddress("glVertexAttrib2dv"));
		VertexAttrib2f = reinterpret_cast<decltype(glVertexAttrib2f)*>(wglGetProcAddress("glVertexAttrib2f"));
		VertexAttrib2fv = reinterpret_cast<decltype(glVertexAttrib2fv)*>(wglGetProcAddress("glVertexAttrib2fv"));
		VertexAttrib2s = reinterpret_cast<decltype(glVertexAttrib2s)*>(wglGetProcAddress("glVertexAttrib2s"));
		VertexAttrib2sv = reinterpret_cast<decltype(glVertexAttrib2sv)*>(wglGetProcAddress("glVertexAttrib2sv"));
		VertexAttrib3d = reinterpret_cast<decltype(glVertexAttrib3d)*>(wglGetProcAddress("glVertexAttrib3d"));
		VertexAttrib3dv = reinterpret_cast<decltype(glVertexAttrib3dv)*>(wglGetProcAddress("glVertexAttrib3dv"));
		VertexAttrib3f = reinterpret_cast<decltype(glVertexAttrib3f)*>(wglGetProcAddress("glVertexAttrib3f"));
		VertexAttrib3fv = reinterpret_cast<decltype(glVertexAttrib3fv)*>(wglGetProcAddress("glVertexAttrib3fv"));
		VertexAttrib3s = reinterpret_cast<decltype(glVertexAttrib3s)*>(wglGetProcAddress("glVertexAttrib3s"));
		VertexAttrib3sv = reinterpret_cast<decltype(glVertexAttrib3sv)*>(wglGetProcAddress("glVertexAttrib3sv"));
		VertexAttrib4Nbv = reinterpret_cast<decltype(glVertexAttrib4Nbv)*>(wglGetProcAddress("glVertexAttrib4Nbv"));
		VertexAttrib4Niv = reinterpret_cast<decltype(glVertexAttrib4Niv)*>(wglGetProcAddress("glVertexAttrib4Niv"));
		VertexAttrib4Nsv = reinterpret_cast<decltype(glVertexAttrib4Nsv)*>(wglGetProcAddress("glVertexAttrib4Nsv"));
		VertexAttrib4Nub = reinterpret_cast<decltype(glVertexAttrib4Nub)*>(wglGetProcAddress("glVertexAttrib4Nub"));
		VertexAttrib4Nubv = reinterpret_cast<decltype(glVertexAttrib4Nubv)*>(wglGetProcAddress("glVertexAttrib4Nubv"));
		VertexAttrib4Nuiv = reinterpret_cast<decltype(glVertexAttrib4Nuiv)*>(wglGetProcAddress("glVertexAttrib4Nuiv"));
		VertexAttrib4Nusv = reinterpret_cast<decltype(glVertexAttrib4Nusv)*>(wglGetProcAddress("glVertexAttrib4Nusv"));
		VertexAttrib4bv = reinterpret_cast<decltype(glVertexAttrib4bv)*>(wglGetProcAddress("glVertexAttrib4bv"));
		VertexAttrib4d = reinterpret_cast<decltype(glVertexAttrib4d)*>(wglGetProcAddress("glVertexAttrib4d"));
		VertexAttrib4dv = reinterpret_cast<decltype(glVertexAttrib4dv)*>(wglGetProcAddress("glVertexAttrib4dv"));
		VertexAttrib4f = reinterpret_cast<decltype(glVertexAttrib4f)*>(wglGetProcAddress("glVertexAttrib4f"));
		VertexAttrib4fv = reinterpret_cast<decltype(glVertexAttrib4fv)*>(wglGetProcAddress("glVertexAttrib4fv"));
		VertexAttrib4iv = reinterpret_cast<decltype(glVertexAttrib4iv)*>(wglGetProcAddress("glVertexAttrib4iv"));
		VertexAttrib4s = reinterpret_cast<decltype(glVertexAttrib4s)*>(wglGetProcAddress("glVertexAttrib4s"));
		VertexAttrib4sv = reinterpret_cast<decltype(glVertexAttrib4sv)*>(wglGetProcAddress("glVertexAttrib4sv"));
		VertexAttrib4ubv = reinterpret_cast<decltype(glVertexAttrib4ubv)*>(wglGetProcAddress("glVertexAttrib4ubv"));
		VertexAttrib4uiv = reinterpret_cast<decltype(glVertexAttrib4uiv)*>(wglGetProcAddress("glVertexAttrib4uiv"));
		VertexAttrib4usv = reinterpret_cast<decltype(glVertexAttrib4usv)*>(wglGetProcAddress("glVertexAttrib4usv"));
		VertexAttribBinding = reinterpret_cast<decltype(glVertexAttribBinding)*>(wglGetProcAddress("glVertexAttribBinding"));
		VertexAttribDivisor = reinterpret_cast<decltype(glVertexAttribDivisor)*>(wglGetProcAddress("glVertexAttribDivisor"));
		VertexAttribFormat = reinterpret_cast<decltype(glVertexAttribFormat)*>(wglGetProcAddress("glVertexAttribFormat"));
		VertexAttribI1i = reinterpret_cast<decltype(glVertexAttribI1i)*>(wglGetProcAddress("glVertexAttribI1i"));
		VertexAttribI1iv = reinterpret_cast<decltype(glVertexAttribI1iv)*>(wglGetProcAddress("glVertexAttribI1iv"));
		VertexAttribI1ui = reinterpret_cast<decltype(glVertexAttribI1ui)*>(wglGetProcAddress("glVertexAttribI1ui"));
		VertexAttribI1uiv = reinterpret_cast<decltype(glVertexAttribI1uiv)*>(wglGetProcAddress("glVertexAttribI1uiv"));
		VertexAttribI2i = reinterpret_cast<decltype(glVertexAttribI2i)*>(wglGetProcAddress("glVertexAttribI2i"));
		VertexAttribI2iv = reinterpret_cast<decltype(glVertexAttribI2iv)*>(wglGetProcAddress("glVertexAttribI2iv"));
		VertexAttribI2ui = reinterpret_cast<decltype(glVertexAttribI2ui)*>(wglGetProcAddress("glVertexAttribI2ui"));
		VertexAttribI2uiv = reinterpret_cast<decltype(glVertexAttribI2uiv)*>(wglGetProcAddress("glVertexAttribI2uiv"));
		VertexAttribI3i = reinterpret_cast<decltype(glVertexAttribI3i)*>(wglGetProcAddress("glVertexAttribI3i"));
		VertexAttribI3iv = reinterpret_cast<decltype(glVertexAttribI3iv)*>(wglGetProcAddress("glVertexAttribI3iv"));
		VertexAttribI3ui = reinterpret_cast<decltype(glVertexAttribI3ui)*>(wglGetProcAddress("glVertexAttribI3ui"));
		VertexAttribI3uiv = reinterpret_cast<decltype(glVertexAttribI3uiv)*>(wglGetProcAddress("glVertexAttribI3uiv"));
		VertexAttribI4bv = reinterpret_cast<decltype(glVertexAttribI4bv)*>(wglGetProcAddress("glVertexAttribI4bv"));
		VertexAttribI4i = reinterpret_cast<decltype(glVertexAttribI4i)*>(wglGetProcAddress("glVertexAttribI4i"));
		VertexAttribI4iv = reinterpret_cast<decltype(glVertexAttribI4iv)*>(wglGetProcAddress("glVertexAttribI4iv"));
		VertexAttribI4sv = reinterpret_cast<decltype(glVertexAttribI4sv)*>(wglGetProcAddress("glVertexAttribI4sv"));
		VertexAttribI4ubv = reinterpret_cast<decltype(glVertexAttribI4ubv)*>(wglGetProcAddress("glVertexAttribI4ubv"));
		VertexAttribI4ui = reinterpret_cast<decltype(glVertexAttribI4ui)*>(wglGetProcAddress("glVertexAttribI4ui"));
		VertexAttribI4uiv = reinterpret_cast<decltype(glVertexAttribI4uiv)*>(wglGetProcAddress("glVertexAttribI4uiv"));
		VertexAttribI4usv = reinterpret_cast<decltype(glVertexAttribI4usv)*>(wglGetProcAddress("glVertexAttribI4usv"));
		VertexAttribIFormat = reinterpret_cast<decltype(glVertexAttribIFormat)*>(wglGetProcAddress("glVertexAttribIFormat"));
		VertexAttribIPointer = reinterpret_cast<decltype(glVertexAttribIPointer)*>(wglGetProcAddress("glVertexAttribIPointer"));
		VertexAttribL1d = reinterpret_cast<decltype(glVertexAttribL1d)*>(wglGetProcAddress("glVertexAttribL1d"));
		VertexAttribL1dv = reinterpret_cast<decltype(glVertexAttribL1dv)*>(wglGetProcAddress("glVertexAttribL1dv"));
		VertexAttribL2d = reinterpret_cast<decltype(glVertexAttribL2d)*>(wglGetProcAddress("glVertexAttribL2d"));
		VertexAttribL2dv = reinterpret_cast<decltype(glVertexAttribL2dv)*>(wglGetProcAddress("glVertexAttribL2dv"));
		VertexAttribL3d = reinterpret_cast<decltype(glVertexAttribL3d)*>(wglGetProcAddress("glVertexAttribL3d"));
		VertexAttribL3dv = reinterpret_cast<decltype(glVertexAttribL3dv)*>(wglGetProcAddress("glVertexAttribL3dv"));
		VertexAttribL4d = reinterpret_cast<decltype(glVertexAttribL4d)*>(wglGetProcAddress("glVertexAttribL4d"));
		VertexAttribL4dv = reinterpret_cast<decltype(glVertexAttribL4dv)*>(wglGetProcAddress("glVertexAttribL4dv"));
		VertexAttribLFormat = reinterpret_cast<decltype(glVertexAttribLFormat)*>(wglGetProcAddress("glVertexAttribLFormat"));
		VertexAttribLPointer = reinterpret_cast<decltype(glVertexAttribLPointer)*>(wglGetProcAddress("glVertexAttribLPointer"));
		VertexAttribP1ui = reinterpret_cast<decltype(glVertexAttribP1ui)*>(wglGetProcAddress("glVertexAttribP1ui"));
		VertexAttribP1uiv = reinterpret_cast<decltype(glVertexAttribP1uiv)*>(wglGetProcAddress("glVertexAttribP1uiv"));
		VertexAttribP2ui = reinterpret_cast<decltype(glVertexAttribP2ui)*>(wglGetProcAddress("glVertexAttribP2ui"));
		VertexAttribP2uiv = reinterpret_cast<decltype(glVertexAttribP2uiv)*>(wglGetProcAddress("glVertexAttribP2uiv"));
		VertexAttribP3ui = reinterpret_cast<decltype(glVertexAttribP3ui)*>(wglGetProcAddress("glVertexAttribP3ui"));
		VertexAttribP3uiv = reinterpret_cast<decltype(glVertexAttribP3uiv)*>(wglGetProcAddress("glVertexAttribP3uiv"));
		VertexAttribP4ui = reinterpret_cast<decltype(glVertexAttribP4ui)*>(wglGetProcAddress("glVertexAttribP4ui"));
		VertexAttribP4uiv = reinterpret_cast<decltype(glVertexAttribP4uiv)*>(wglGetProcAddress("glVertexAttribP4uiv"));
		VertexAttribPointer = reinterpret_cast<decltype(glVertexAttribPointer)*>(wglGetProcAddress("glVertexAttribPointer"));
		VertexBindingDivisor = reinterpret_cast<decltype(glVertexBindingDivisor)*>(wglGetProcAddress("glVertexBindingDivisor"));
		ViewportArrayv = reinterpret_cast<decltype(glViewportArrayv)*>(wglGetProcAddress("glViewportArrayv"));
		ViewportIndexedf = reinterpret_cast<decltype(glViewportIndexedf)*>(wglGetProcAddress("glViewportIndexedf"));
		ViewportIndexedfv = reinterpret_cast<decltype(glViewportIndexedfv)*>(wglGetProcAddress("glViewportIndexedfv"));
		WaitSync = reinterpret_cast<decltype(glWaitSync)*>(wglGetProcAddress("glWaitSync"));

		wglSwapInterval = reinterpret_cast<decltype(wglSwapIntervalEXT)*>(wglGetProcAddress("wglSwapIntervalEXT"));

		if (ActiveShaderProgram == nullptr ||
		    ActiveTexture == nullptr ||
		    AttachShader == nullptr ||
		    BeginConditionalRender == nullptr ||
		    BeginQuery == nullptr ||
		    BeginQueryIndexed == nullptr ||
		    BeginTransformFeedback == nullptr ||
		    BindAttribLocation == nullptr ||
		    BindBuffer == nullptr ||
		    BindBufferBase == nullptr ||
		    BindBufferRange == nullptr ||
		    BindBuffersBase == nullptr ||
		    BindBuffersRange == nullptr ||
		    BindFragDataLocation == nullptr ||
		    BindFragDataLocationIndexed == nullptr ||
		    BindFramebuffer == nullptr ||
		    BindImageTexture == nullptr ||
		    BindImageTextures == nullptr ||
		    BindProgramPipeline == nullptr ||
		    BindRenderbuffer == nullptr ||
		    BindSampler == nullptr ||
		    BindSamplers == nullptr ||
		    BindTextureUnit == nullptr ||
		    BindTextures == nullptr ||
		    BindTransformFeedback == nullptr ||
		    BindVertexArray == nullptr ||
		    BindVertexBuffer == nullptr ||
		    BindVertexBuffers == nullptr ||
		    BlendColor == nullptr ||
		    BlendEquation == nullptr ||
		    BlendEquationSeparate == nullptr ||
		    BlendEquationSeparatei == nullptr ||
		    BlendEquationi == nullptr ||
		    BlendFuncSeparate == nullptr ||
		    BlendFuncSeparatei == nullptr ||
		    BlendFunci == nullptr ||
		    BlitFramebuffer == nullptr ||
		    BlitNamedFramebuffer == nullptr ||
		    BufferData == nullptr ||
		    BufferStorage == nullptr ||
		    BufferSubData == nullptr ||
		    CheckFramebufferStatus == nullptr ||
		    CheckNamedFramebufferStatus == nullptr ||
		    ClampColor == nullptr ||
		    ClearBufferData == nullptr ||
		    ClearBufferSubData == nullptr ||
		    ClearBufferfi == nullptr ||
		    ClearBufferfv == nullptr ||
		    ClearBufferiv == nullptr ||
		    ClearBufferuiv == nullptr ||
		    ClearDepthf == nullptr ||
		    ClearNamedBufferData == nullptr ||
		    ClearNamedBufferSubData == nullptr ||
		    ClearNamedFramebufferfi == nullptr ||
		    ClearNamedFramebufferfv == nullptr ||
		    ClearNamedFramebufferiv == nullptr ||
		    ClearNamedFramebufferuiv == nullptr ||
		    ClearTexImage == nullptr ||
		    ClearTexSubImage == nullptr ||
		    ClientWaitSync == nullptr ||
		    ClipControl == nullptr ||
		    ColorMaski == nullptr ||
		    CompileShader == nullptr ||
		    CompressedTexImage1D == nullptr ||
		    CompressedTexImage2D == nullptr ||
		    CompressedTexImage3D == nullptr ||
		    CompressedTexSubImage1D == nullptr ||
		    CompressedTexSubImage2D == nullptr ||
		    CompressedTexSubImage3D == nullptr ||
		    CompressedTextureSubImage1D == nullptr ||
		    CompressedTextureSubImage2D == nullptr ||
		    CompressedTextureSubImage3D == nullptr ||
		    CopyBufferSubData == nullptr ||
		    CopyImageSubData == nullptr ||
		    CopyNamedBufferSubData == nullptr ||
		    CopyTexSubImage3D == nullptr ||
		    CopyTextureSubImage1D == nullptr ||
		    CopyTextureSubImage2D == nullptr ||
		    CopyTextureSubImage3D == nullptr ||
		    CreateBuffers == nullptr ||
		    CreateFramebuffers == nullptr ||
		    CreateProgram == nullptr ||
		    CreateProgramPipelines == nullptr ||
		    CreateQueries == nullptr ||
		    CreateRenderbuffers == nullptr ||
		    CreateSamplers == nullptr ||
		    CreateShader == nullptr ||
		    CreateShaderProgramv == nullptr ||
		    CreateTextures == nullptr ||
		    CreateTransformFeedbacks == nullptr ||
		    CreateVertexArrays == nullptr ||
		    DebugMessageCallback == nullptr ||
		    DebugMessageControl == nullptr ||
		    DebugMessageInsert == nullptr ||
		    DeleteBuffers == nullptr ||
		    DeleteFramebuffers == nullptr ||
		    DeleteProgram == nullptr ||
		    DeleteProgramPipelines == nullptr ||
		    DeleteQueries == nullptr ||
		    DeleteRenderbuffers == nullptr ||
		    DeleteSamplers == nullptr ||
		    DeleteShader == nullptr ||
		    DeleteSync == nullptr ||
		    DeleteTransformFeedbacks == nullptr ||
		    DeleteVertexArrays == nullptr ||
		    DepthRangeArrayv == nullptr ||
		    DepthRangeIndexed == nullptr ||
		    DepthRangef == nullptr ||
		    DetachShader == nullptr ||
		    DisableVertexArrayAttrib == nullptr ||
		    DisableVertexAttribArray == nullptr ||
		    Disablei == nullptr ||
		    DispatchCompute == nullptr ||
		    DispatchComputeIndirect == nullptr ||
		    DrawArraysIndirect == nullptr ||
		    DrawArraysInstanced == nullptr ||
		    DrawArraysInstancedBaseInstance == nullptr ||
		    DrawBuffers == nullptr ||
		    DrawElementsBaseVertex == nullptr ||
		    DrawElementsIndirect == nullptr ||
		    DrawElementsInstanced == nullptr ||
		    DrawElementsInstancedBaseInstance == nullptr ||
		    DrawElementsInstancedBaseVertex == nullptr ||
		    DrawElementsInstancedBaseVertexBaseInstance == nullptr ||
		    DrawRangeElements == nullptr ||
		    DrawRangeElementsBaseVertex == nullptr ||
		    DrawTransformFeedback == nullptr ||
		    DrawTransformFeedbackInstanced == nullptr ||
		    DrawTransformFeedbackStream == nullptr ||
		    DrawTransformFeedbackStreamInstanced == nullptr ||
		    EnableVertexArrayAttrib == nullptr ||
		    EnableVertexAttribArray == nullptr ||
		    Enablei == nullptr ||
		    EndConditionalRender == nullptr ||
		    EndQuery == nullptr ||
		    EndQueryIndexed == nullptr ||
		    EndTransformFeedback == nullptr ||
		    FenceSync == nullptr ||
		    FlushMappedBufferRange == nullptr ||
		    FlushMappedNamedBufferRange == nullptr ||
		    FramebufferParameteri == nullptr ||
		    FramebufferRenderbuffer == nullptr ||
		    FramebufferTexture == nullptr ||
		    FramebufferTexture1D == nullptr ||
		    FramebufferTexture2D == nullptr ||
		    FramebufferTexture3D == nullptr ||
		    FramebufferTextureLayer == nullptr ||
		    GenBuffers == nullptr ||
		    GenFramebuffers == nullptr ||
		    GenProgramPipelines == nullptr ||
		    GenQueries == nullptr ||
		    GenRenderbuffers == nullptr ||
		    GenSamplers == nullptr ||
		    GenTransformFeedbacks == nullptr ||
		    GenVertexArrays == nullptr ||
		    GenerateMipmap == nullptr ||
		    GenerateTextureMipmap == nullptr ||
		    GetActiveAtomicCounterBufferiv == nullptr ||
		    GetActiveAttrib == nullptr ||
		    GetActiveSubroutineName == nullptr ||
		    GetActiveSubroutineUniformName == nullptr ||
		    GetActiveSubroutineUniformiv == nullptr ||
		    GetActiveUniform == nullptr ||
		    GetActiveUniformBlockName == nullptr ||
		    GetActiveUniformBlockiv == nullptr ||
		    GetActiveUniformName == nullptr ||
		    GetActiveUniformsiv == nullptr ||
		    GetAttachedShaders == nullptr ||
		    GetAttribLocation == nullptr ||
		    GetBooleani_v == nullptr ||
		    GetBufferParameteri64v == nullptr ||
		    GetBufferParameteriv == nullptr ||
		    GetBufferPointerv == nullptr ||
		    GetBufferSubData == nullptr ||
		    GetCompressedTexImage == nullptr ||
		    GetCompressedTextureImage == nullptr ||
		    GetCompressedTextureSubImage == nullptr ||
		    GetDebugMessageLog == nullptr ||
		    GetDoublei_v == nullptr ||
		    GetFloati_v == nullptr ||
		    GetFragDataIndex == nullptr ||
		    GetFragDataLocation == nullptr ||
		    GetFramebufferAttachmentParameteriv == nullptr ||
		    GetFramebufferParameteriv == nullptr ||
		    GetGraphicsResetStatus == nullptr ||
		    GetInteger64i_v == nullptr ||
		    GetInteger64v == nullptr ||
		    GetIntegeri_v == nullptr ||
		    GetInternalformati64v == nullptr ||
		    GetInternalformativ == nullptr ||
		    GetMultisamplefv == nullptr ||
		    GetNamedBufferParameteri64v == nullptr ||
		    GetNamedBufferParameteriv == nullptr ||
		    GetNamedBufferPointerv == nullptr ||
		    GetNamedBufferSubData == nullptr ||
		    GetNamedFramebufferAttachmentParameteriv == nullptr ||
		    GetNamedFramebufferParameteriv == nullptr ||
		    GetNamedRenderbufferParameteriv == nullptr ||
		    GetObjectLabel == nullptr ||
		    GetObjectPtrLabel == nullptr ||
		    GetProgramBinary == nullptr ||
		    GetProgramInfoLog == nullptr ||
		    GetProgramInterfaceiv == nullptr ||
		    GetProgramPipelineInfoLog == nullptr ||
		    GetProgramPipelineiv == nullptr ||
		    GetProgramResourceIndex == nullptr ||
		    GetProgramResourceLocation == nullptr ||
		    GetProgramResourceLocationIndex == nullptr ||
		    GetProgramResourceName == nullptr ||
		    GetProgramResourceiv == nullptr ||
		    GetProgramStageiv == nullptr ||
		    GetProgramiv == nullptr ||
		    GetQueryBufferObjecti64v == nullptr ||
		    GetQueryBufferObjectiv == nullptr ||
		    GetQueryBufferObjectui64v == nullptr ||
		    GetQueryBufferObjectuiv == nullptr ||
		    GetQueryIndexediv == nullptr ||
		    GetQueryObjecti64v == nullptr ||
		    GetQueryObjectiv == nullptr ||
		    GetQueryObjectui64v == nullptr ||
		    GetQueryObjectuiv == nullptr ||
		    GetQueryiv == nullptr ||
		    GetRenderbufferParameteriv == nullptr ||
		    GetSamplerParameterIiv == nullptr ||
		    GetSamplerParameterIuiv == nullptr ||
		    GetSamplerParameterfv == nullptr ||
		    GetSamplerParameteriv == nullptr ||
		    GetShaderInfoLog == nullptr ||
		    GetShaderPrecisionFormat == nullptr ||
		    GetShaderSource == nullptr ||
		    GetShaderiv == nullptr ||
		    GetStringi == nullptr ||
		    GetSubroutineIndex == nullptr ||
		    GetSubroutineUniformLocation == nullptr ||
		    GetSynciv == nullptr ||
		    GetTexParameterIiv == nullptr ||
		    GetTexParameterIuiv == nullptr ||
		    GetTextureImage == nullptr ||
		    GetTextureLevelParameterfv == nullptr ||
		    GetTextureLevelParameteriv == nullptr ||
		    GetTextureParameterIiv == nullptr ||
		    GetTextureParameterIuiv == nullptr ||
		    GetTextureParameterfv == nullptr ||
		    GetTextureParameteriv == nullptr ||
		    GetTextureSubImage == nullptr ||
		    GetTransformFeedbackVarying == nullptr ||
		    GetTransformFeedbacki64_v == nullptr ||
		    GetTransformFeedbacki_v == nullptr ||
		    GetTransformFeedbackiv == nullptr ||
		    GetUniformBlockIndex == nullptr ||
		    GetUniformIndices == nullptr ||
		    GetUniformLocation == nullptr ||
		    GetUniformSubroutineuiv == nullptr ||
		    GetUniformdv == nullptr ||
		    GetUniformfv == nullptr ||
		    GetUniformiv == nullptr ||
		    GetUniformuiv == nullptr ||
		    GetVertexArrayIndexed64iv == nullptr ||
		    GetVertexArrayIndexediv == nullptr ||
		    GetVertexArrayiv == nullptr ||
		    GetVertexAttribIiv == nullptr ||
		    GetVertexAttribIuiv == nullptr ||
		    GetVertexAttribLdv == nullptr ||
		    GetVertexAttribPointerv == nullptr ||
		    GetVertexAttribdv == nullptr ||
		    GetVertexAttribfv == nullptr ||
		    GetVertexAttribiv == nullptr ||
		    GetnCompressedTexImage == nullptr ||
		    GetnTexImage == nullptr ||
		    GetnUniformdv == nullptr ||
		    GetnUniformfv == nullptr ||
		    GetnUniformiv == nullptr ||
		    GetnUniformuiv == nullptr ||
		    InvalidateBufferData == nullptr ||
		    InvalidateBufferSubData == nullptr ||
		    InvalidateFramebuffer == nullptr ||
		    InvalidateNamedFramebufferData == nullptr ||
		    InvalidateNamedFramebufferSubData == nullptr ||
		    InvalidateSubFramebuffer == nullptr ||
		    InvalidateTexImage == nullptr ||
		    InvalidateTexSubImage == nullptr ||
		    IsBuffer == nullptr ||
		    IsEnabledi == nullptr ||
		    IsFramebuffer == nullptr ||
		    IsProgram == nullptr ||
		    IsProgramPipeline == nullptr ||
		    IsQuery == nullptr ||
		    IsRenderbuffer == nullptr ||
		    IsSampler == nullptr ||
		    IsShader == nullptr ||
		    IsSync == nullptr ||
		    IsTransformFeedback == nullptr ||
		    IsVertexArray == nullptr ||
		    LinkProgram == nullptr ||
		    MapBuffer == nullptr ||
		    MapBufferRange == nullptr ||
		    MapNamedBuffer == nullptr ||
		    MapNamedBufferRange == nullptr ||
		    MemoryBarrier == nullptr ||
		    MemoryBarrierByRegion == nullptr ||
		    MinSampleShading == nullptr ||
		    MultiDrawArrays == nullptr ||
		    MultiDrawArraysIndirect == nullptr ||
		    MultiDrawElements == nullptr ||
		    MultiDrawElementsBaseVertex == nullptr ||
		    MultiDrawElementsIndirect == nullptr ||
		    NamedBufferData == nullptr ||
		    NamedBufferStorage == nullptr ||
		    NamedBufferSubData == nullptr ||
		    NamedFramebufferDrawBuffer == nullptr ||
		    NamedFramebufferDrawBuffers == nullptr ||
		    NamedFramebufferParameteri == nullptr ||
		    NamedFramebufferReadBuffer == nullptr ||
		    NamedFramebufferRenderbuffer == nullptr ||
		    NamedFramebufferTexture == nullptr ||
		    NamedFramebufferTextureLayer == nullptr ||
		    NamedRenderbufferStorage == nullptr ||
		    NamedRenderbufferStorageMultisample == nullptr ||
		    ObjectLabel == nullptr ||
		    ObjectPtrLabel == nullptr ||
		    PatchParameterfv == nullptr ||
		    PatchParameteri == nullptr ||
		    PauseTransformFeedback == nullptr ||
		    PointParameterf == nullptr ||
		    PointParameterfv == nullptr ||
		    PointParameteri == nullptr ||
		    PointParameteriv == nullptr ||
		    PopDebugGroup == nullptr ||
		    PrimitiveRestartIndex == nullptr ||
		    ProgramBinary == nullptr ||
		    ProgramParameteri == nullptr ||
		    ProgramUniform1d == nullptr ||
		    ProgramUniform1dv == nullptr ||
		    ProgramUniform1f == nullptr ||
		    ProgramUniform1fv == nullptr ||
		    ProgramUniform1i == nullptr ||
		    ProgramUniform1iv == nullptr ||
		    ProgramUniform1ui == nullptr ||
		    ProgramUniform1uiv == nullptr ||
		    ProgramUniform2d == nullptr ||
		    ProgramUniform2dv == nullptr ||
		    ProgramUniform2f == nullptr ||
		    ProgramUniform2fv == nullptr ||
		    ProgramUniform2i == nullptr ||
		    ProgramUniform2iv == nullptr ||
		    ProgramUniform2ui == nullptr ||
		    ProgramUniform2uiv == nullptr ||
		    ProgramUniform3d == nullptr ||
		    ProgramUniform3dv == nullptr ||
		    ProgramUniform3f == nullptr ||
		    ProgramUniform3fv == nullptr ||
		    ProgramUniform3i == nullptr ||
		    ProgramUniform3iv == nullptr ||
		    ProgramUniform3ui == nullptr ||
		    ProgramUniform3uiv == nullptr ||
		    ProgramUniform4d == nullptr ||
		    ProgramUniform4dv == nullptr ||
		    ProgramUniform4f == nullptr ||
		    ProgramUniform4fv == nullptr ||
		    ProgramUniform4i == nullptr ||
		    ProgramUniform4iv == nullptr ||
		    ProgramUniform4ui == nullptr ||
		    ProgramUniform4uiv == nullptr ||
		    ProgramUniformMatrix2dv == nullptr ||
		    ProgramUniformMatrix2fv == nullptr ||
		    ProgramUniformMatrix2x3dv == nullptr ||
		    ProgramUniformMatrix2x3fv == nullptr ||
		    ProgramUniformMatrix2x4dv == nullptr ||
		    ProgramUniformMatrix2x4fv == nullptr ||
		    ProgramUniformMatrix3dv == nullptr ||
		    ProgramUniformMatrix3fv == nullptr ||
		    ProgramUniformMatrix3x2dv == nullptr ||
		    ProgramUniformMatrix3x2fv == nullptr ||
		    ProgramUniformMatrix3x4dv == nullptr ||
		    ProgramUniformMatrix3x4fv == nullptr ||
		    ProgramUniformMatrix4dv == nullptr ||
		    ProgramUniformMatrix4fv == nullptr ||
		    ProgramUniformMatrix4x2dv == nullptr ||
		    ProgramUniformMatrix4x2fv == nullptr ||
		    ProgramUniformMatrix4x3dv == nullptr ||
		    ProgramUniformMatrix4x3fv == nullptr ||
		    ProvokingVertex == nullptr ||
		    PushDebugGroup == nullptr ||
		    QueryCounter == nullptr ||
		    ReadnPixels == nullptr ||
		    ReleaseShaderCompiler == nullptr ||
		    RenderbufferStorage == nullptr ||
		    RenderbufferStorageMultisample == nullptr ||
		    ResumeTransformFeedback == nullptr ||
		    SampleCoverage == nullptr ||
		    SampleMaski == nullptr ||
		    SamplerParameterIiv == nullptr ||
		    SamplerParameterIuiv == nullptr ||
		    SamplerParameterf == nullptr ||
		    SamplerParameterfv == nullptr ||
		    SamplerParameteri == nullptr ||
		    SamplerParameteriv == nullptr ||
		    ScissorArrayv == nullptr ||
		    ScissorIndexed == nullptr ||
		    ScissorIndexedv == nullptr ||
		    ShaderBinary == nullptr ||
		    ShaderSource == nullptr ||
		    ShaderStorageBlockBinding == nullptr ||
		    StencilFuncSeparate == nullptr ||
		    StencilMaskSeparate == nullptr ||
		    StencilOpSeparate == nullptr ||
		    TexBuffer == nullptr ||
		    TexBufferRange == nullptr ||
		    TexImage2DMultisample == nullptr ||
		    TexImage3D == nullptr ||
		    TexImage3DMultisample == nullptr ||
		    TexParameterIiv == nullptr ||
		    TexParameterIuiv == nullptr ||
		    TexStorage1D == nullptr ||
		    TexStorage2D == nullptr ||
		    TexStorage2DMultisample == nullptr ||
		    TexStorage3D == nullptr ||
		    TexStorage3DMultisample == nullptr ||
		    TexSubImage3D == nullptr ||
		    TextureBarrier == nullptr ||
		    TextureBuffer == nullptr ||
		    TextureBufferRange == nullptr ||
		    TextureParameterIiv == nullptr ||
		    TextureParameterIuiv == nullptr ||
		    TextureParameterf == nullptr ||
		    TextureParameterfv == nullptr ||
		    TextureParameteri == nullptr ||
		    TextureParameteriv == nullptr ||
		    TextureStorage1D == nullptr ||
		    TextureStorage2D == nullptr ||
		    TextureStorage2DMultisample == nullptr ||
		    TextureStorage3D == nullptr ||
		    TextureStorage3DMultisample == nullptr ||
		    TextureSubImage1D == nullptr ||
		    TextureSubImage2D == nullptr ||
		    TextureSubImage3D == nullptr ||
		    TextureView == nullptr ||
		    TransformFeedbackBufferBase == nullptr ||
		    TransformFeedbackBufferRange == nullptr ||
		    TransformFeedbackVaryings == nullptr ||
		    Uniform1d == nullptr ||
		    Uniform1dv == nullptr ||
		    Uniform1f == nullptr ||
		    Uniform1fv == nullptr ||
		    Uniform1i == nullptr ||
		    Uniform1iv == nullptr ||
		    Uniform1ui == nullptr ||
		    Uniform1uiv == nullptr ||
		    Uniform2d == nullptr ||
		    Uniform2dv == nullptr ||
		    Uniform2f == nullptr ||
		    Uniform2fv == nullptr ||
		    Uniform2i == nullptr ||
		    Uniform2iv == nullptr ||
		    Uniform2ui == nullptr ||
		    Uniform2uiv == nullptr ||
		    Uniform3d == nullptr ||
		    Uniform3dv == nullptr ||
		    Uniform3f == nullptr ||
		    Uniform3fv == nullptr ||
		    Uniform3i == nullptr ||
		    Uniform3iv == nullptr ||
		    Uniform3ui == nullptr ||
		    Uniform3uiv == nullptr ||
		    Uniform4d == nullptr ||
		    Uniform4dv == nullptr ||
		    Uniform4f == nullptr ||
		    Uniform4fv == nullptr ||
		    Uniform4i == nullptr ||
		    Uniform4iv == nullptr ||
		    Uniform4ui == nullptr ||
		    Uniform4uiv == nullptr ||
		    UniformBlockBinding == nullptr ||
		    UniformMatrix2dv == nullptr ||
		    UniformMatrix2fv == nullptr ||
		    UniformMatrix2x3dv == nullptr ||
		    UniformMatrix2x3fv == nullptr ||
		    UniformMatrix2x4dv == nullptr ||
		    UniformMatrix2x4fv == nullptr ||
		    UniformMatrix3dv == nullptr ||
		    UniformMatrix3fv == nullptr ||
		    UniformMatrix3x2dv == nullptr ||
		    UniformMatrix3x2fv == nullptr ||
		    UniformMatrix3x4dv == nullptr ||
		    UniformMatrix3x4fv == nullptr ||
		    UniformMatrix4dv == nullptr ||
		    UniformMatrix4fv == nullptr ||
		    UniformMatrix4x2dv == nullptr ||
		    UniformMatrix4x2fv == nullptr ||
		    UniformMatrix4x3dv == nullptr ||
		    UniformMatrix4x3fv == nullptr ||
		    UniformSubroutinesuiv == nullptr ||
		    UnmapBuffer == nullptr ||
		    UnmapNamedBuffer == nullptr ||
		    UseProgram == nullptr ||
		    UseProgramStages == nullptr ||
		    ValidateProgram == nullptr ||
		    ValidateProgramPipeline == nullptr ||
		    VertexArrayAttribBinding == nullptr ||
		    VertexArrayAttribFormat == nullptr ||
		    VertexArrayAttribIFormat == nullptr ||
		    VertexArrayAttribLFormat == nullptr ||
		    VertexArrayBindingDivisor == nullptr ||
		    VertexArrayElementBuffer == nullptr ||
		    VertexArrayVertexBuffer == nullptr ||
		    VertexArrayVertexBuffers == nullptr ||
		    VertexAttrib1d == nullptr ||
		    VertexAttrib1dv == nullptr ||
		    VertexAttrib1f == nullptr ||
		    VertexAttrib1fv == nullptr ||
		    VertexAttrib1s == nullptr ||
		    VertexAttrib1sv == nullptr ||
		    VertexAttrib2d == nullptr ||
		    VertexAttrib2dv == nullptr ||
		    VertexAttrib2f == nullptr ||
		    VertexAttrib2fv == nullptr ||
		    VertexAttrib2s == nullptr ||
		    VertexAttrib2sv == nullptr ||
		    VertexAttrib3d == nullptr ||
		    VertexAttrib3dv == nullptr ||
		    VertexAttrib3f == nullptr ||
		    VertexAttrib3fv == nullptr ||
		    VertexAttrib3s == nullptr ||
		    VertexAttrib3sv == nullptr ||
		    VertexAttrib4Nbv == nullptr ||
		    VertexAttrib4Niv == nullptr ||
		    VertexAttrib4Nsv == nullptr ||
		    VertexAttrib4Nub == nullptr ||
		    VertexAttrib4Nubv == nullptr ||
		    VertexAttrib4Nuiv == nullptr ||
		    VertexAttrib4Nusv == nullptr ||
		    VertexAttrib4bv == nullptr ||
		    VertexAttrib4d == nullptr ||
		    VertexAttrib4dv == nullptr ||
		    VertexAttrib4f == nullptr ||
		    VertexAttrib4fv == nullptr ||
		    VertexAttrib4iv == nullptr ||
		    VertexAttrib4s == nullptr ||
		    VertexAttrib4sv == nullptr ||
		    VertexAttrib4ubv == nullptr ||
		    VertexAttrib4uiv == nullptr ||
		    VertexAttrib4usv == nullptr ||
		    VertexAttribBinding == nullptr ||
		    VertexAttribDivisor == nullptr ||
		    VertexAttribFormat == nullptr ||
		    VertexAttribI1i == nullptr ||
		    VertexAttribI1iv == nullptr ||
		    VertexAttribI1ui == nullptr ||
		    VertexAttribI1uiv == nullptr ||
		    VertexAttribI2i == nullptr ||
		    VertexAttribI2iv == nullptr ||
		    VertexAttribI2ui == nullptr ||
		    VertexAttribI2uiv == nullptr ||
		    VertexAttribI3i == nullptr ||
		    VertexAttribI3iv == nullptr ||
		    VertexAttribI3ui == nullptr ||
		    VertexAttribI3uiv == nullptr ||
		    VertexAttribI4bv == nullptr ||
		    VertexAttribI4i == nullptr ||
		    VertexAttribI4iv == nullptr ||
		    VertexAttribI4sv == nullptr ||
		    VertexAttribI4ubv == nullptr ||
		    VertexAttribI4ui == nullptr ||
		    VertexAttribI4uiv == nullptr ||
		    VertexAttribI4usv == nullptr ||
		    VertexAttribIFormat == nullptr ||
		    VertexAttribIPointer == nullptr ||
		    VertexAttribL1d == nullptr ||
		    VertexAttribL1dv == nullptr ||
		    VertexAttribL2d == nullptr ||
		    VertexAttribL2dv == nullptr ||
		    VertexAttribL3d == nullptr ||
		    VertexAttribL3dv == nullptr ||
		    VertexAttribL4d == nullptr ||
		    VertexAttribL4dv == nullptr ||
		    VertexAttribLFormat == nullptr ||
		    VertexAttribLPointer == nullptr ||
		    VertexAttribP1ui == nullptr ||
		    VertexAttribP1uiv == nullptr ||
		    VertexAttribP2ui == nullptr ||
		    VertexAttribP2uiv == nullptr ||
		    VertexAttribP3ui == nullptr ||
		    VertexAttribP3uiv == nullptr ||
		    VertexAttribP4ui == nullptr ||
		    VertexAttribP4uiv == nullptr ||
		    VertexAttribPointer == nullptr ||
		    VertexBindingDivisor == nullptr ||
		    ViewportArrayv == nullptr ||
		    ViewportIndexedf == nullptr ||
		    ViewportIndexedfv == nullptr ||
		    WaitSync == nullptr ||
		    wglSwapInterval == nullptr)
			return; // throw std::runtime_error("OpenGL IAT initialization failed");
	}

	GLCOREAPI const glcoreContext* APIENTRY glcoreContextInit()
	{
		return new glcoreContext;
	}
	
	GLCOREAPI void APIENTRY glcoreContextDestroy(const glcoreContext* ctx)
	{
		delete ctx;
	}
	
	GLCOREAPI void APIENTRY glcoreContextMakeCurrent(const glcoreContext* ctx)
	{
		context = ctx;
	}
	
	GLCOREAPI const glcoreContext* APIENTRY glcoreContextGetCurrent()
	{
		return context;
	}


	GLCOREAPI void APIENTRY glActiveShaderProgram(GLuint pipeline, GLuint program)
	{
		return context->ActiveShaderProgram(pipeline, program);
	}

	GLCOREAPI void APIENTRY glActiveTexture(GLenum texture)
	{
		return context->ActiveTexture(texture);
	}

	GLCOREAPI void APIENTRY glAttachShader(GLuint program, GLuint shader)
	{
		return context->AttachShader(program, shader);
	}

	GLCOREAPI void APIENTRY glBeginConditionalRender(GLuint id, GLenum mode)
	{
		return context->BeginConditionalRender(id, mode);
	}

	GLCOREAPI void APIENTRY glBeginQuery(GLenum target, GLuint id)
	{
		return context->BeginQuery(target, id);
	}

	GLCOREAPI void APIENTRY glBeginQueryIndexed(GLenum target, GLuint index, GLuint id)
	{
		return context->BeginQueryIndexed(target, index, id);
	}

	GLCOREAPI void APIENTRY glBeginTransformFeedback(GLenum primitiveMode)
	{
		return context->BeginTransformFeedback(primitiveMode);
	}

	GLCOREAPI void APIENTRY glBindAttribLocation(GLuint program, GLuint index, const GLchar* name)
	{
		return context->BindAttribLocation(program, index, name);
	}

	GLCOREAPI void APIENTRY glBindBuffer(GLenum target, GLuint buffer)
	{
		return context->BindBuffer(target, buffer);
	}

	GLCOREAPI void APIENTRY glBindBufferBase(GLenum target, GLuint index, GLuint buffer)
	{
		return context->BindBufferBase(target, index, buffer);
	}

	GLCOREAPI void APIENTRY glBindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size)
	{
		return context->BindBufferRange(target, index, buffer, offset, size);
	}

	GLCOREAPI void APIENTRY glBindBuffersBase(GLenum target, GLuint first, GLsizei count, const GLuint* buffers)
	{
		return context->BindBuffersBase(target, first, count, buffers);
	}

	GLCOREAPI void APIENTRY glBindBuffersRange(GLenum target, GLuint first, GLsizei count, const GLuint* buffers, const GLintptr* offsets, const GLsizeiptr* sizes)
	{
		return context->BindBuffersRange(target, first, count, buffers, offsets, sizes);
	}

	GLCOREAPI void APIENTRY glBindFragDataLocation(GLuint program, GLuint color, const GLchar* name)
	{
		return context->BindFragDataLocation(program, color, name);
	}

	GLCOREAPI void APIENTRY glBindFragDataLocationIndexed(GLuint program, GLuint colorNumber, GLuint index, const GLchar* name)
	{
		return context->BindFragDataLocationIndexed(program, colorNumber, index, name);
	}

	GLCOREAPI void APIENTRY glBindFramebuffer(GLenum target, GLuint framebuffer)
	{
		return context->BindFramebuffer(target, framebuffer);
	}

	GLCOREAPI void APIENTRY glBindImageTexture(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format)
	{
		return context->BindImageTexture(unit, texture, level, layered, layer, access, format);
	}

	GLCOREAPI void APIENTRY glBindImageTextures(GLuint first, GLsizei count, const GLuint* textures)
	{
		return context->BindImageTextures(first, count, textures);
	}

	GLCOREAPI void APIENTRY glBindProgramPipeline(GLuint pipeline)
	{
		return context->BindProgramPipeline(pipeline);
	}

	GLCOREAPI void APIENTRY glBindRenderbuffer(GLenum target, GLuint renderbuffer)
	{
		return context->BindRenderbuffer(target, renderbuffer);
	}

	GLCOREAPI void APIENTRY glBindSampler(GLuint unit, GLuint sampler)
	{
		return context->BindSampler(unit, sampler);
	}

	GLCOREAPI void APIENTRY glBindSamplers(GLuint first, GLsizei count, const GLuint* samplers)
	{
		return context->BindSamplers(first, count, samplers);
	}

	GLCOREAPI void APIENTRY glBindTextureUnit(GLuint unit, GLuint texture)
	{
		return context->BindTextureUnit(unit, texture);
	}

	GLCOREAPI void APIENTRY glBindTextures(GLuint first, GLsizei count, const GLuint* textures)
	{
		return context->BindTextures(first, count, textures);
	}

	GLCOREAPI void APIENTRY glBindTransformFeedback(GLenum target, GLuint id)
	{
		return context->BindTransformFeedback(target, id);
	}

	GLCOREAPI void APIENTRY glBindVertexArray(GLuint array)
	{
		return context->BindVertexArray(array);
	}

	GLCOREAPI void APIENTRY glBindVertexBuffer(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride)
	{
		return context->BindVertexBuffer(bindingindex, buffer, offset, stride);
	}

	GLCOREAPI void APIENTRY glBindVertexBuffers(GLuint first, GLsizei count, const GLuint* buffers, const GLintptr* offsets, const GLsizei* strides)
	{
		return context->BindVertexBuffers(first, count, buffers, offsets, strides);
	}

	GLCOREAPI void APIENTRY glBlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
	{
		return context->BlendColor(red, green, blue, alpha);
	}

	GLCOREAPI void APIENTRY glBlendEquation(GLenum mode)
	{
		return context->BlendEquation(mode);
	}

	GLCOREAPI void APIENTRY glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
	{
		return context->BlendEquationSeparate(modeRGB, modeAlpha);
	}

	GLCOREAPI void APIENTRY glBlendEquationSeparatei(GLuint buf, GLenum modeRGB, GLenum modeAlpha)
	{
		return context->BlendEquationSeparatei(buf, modeRGB, modeAlpha);
	}

	GLCOREAPI void APIENTRY glBlendEquationi(GLuint buf, GLenum mode)
	{
		return context->BlendEquationi(buf, mode);
	}

	GLCOREAPI void APIENTRY glBlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha)
	{
		return context->BlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
	}

	GLCOREAPI void APIENTRY glBlendFuncSeparatei(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
	{
		return context->BlendFuncSeparatei(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
	}

	GLCOREAPI void APIENTRY glBlendFunci(GLuint buf, GLenum src, GLenum dst)
	{
		return context->BlendFunci(buf, src, dst);
	}

	GLCOREAPI void APIENTRY glBlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)
	{
		return context->BlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
	}

	GLCOREAPI void APIENTRY glBlitNamedFramebuffer(GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)
	{
		return context->BlitNamedFramebuffer(readFramebuffer, drawFramebuffer, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
	}

	GLCOREAPI void APIENTRY glBufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage)
	{
		return context->BufferData(target, size, data, usage);
	}

	GLCOREAPI void APIENTRY glBufferStorage(GLenum target, GLsizeiptr size, const void* data, GLbitfield flags)
	{
		return context->BufferStorage(target, size, data, flags);
	}

	GLCOREAPI void APIENTRY glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void* data)
	{
		return context->BufferSubData(target, offset, size, data);
	}

	GLCOREAPI GLenum APIENTRY glCheckFramebufferStatus(GLenum target)
	{
		return context->CheckFramebufferStatus(target);
	}

	GLCOREAPI GLenum APIENTRY glCheckNamedFramebufferStatus(GLuint framebuffer, GLenum target)
	{
		return context->CheckNamedFramebufferStatus(framebuffer, target);
	}

	GLCOREAPI void APIENTRY glClampColor(GLenum target, GLenum clamp)
	{
		return context->ClampColor(target, clamp);
	}

	GLCOREAPI void APIENTRY glClearBufferData(GLenum target, GLenum internalformat, GLenum format, GLenum type, const void* data)
	{
		return context->ClearBufferData(target, internalformat, format, type, data);
	}

	GLCOREAPI void APIENTRY glClearBufferSubData(GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void* data)
	{
		return context->ClearBufferSubData(target, internalformat, offset, size, format, type, data);
	}

	GLCOREAPI void APIENTRY glClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil)
	{
		return context->ClearBufferfi(buffer, drawbuffer, depth, stencil);
	}

	GLCOREAPI void APIENTRY glClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat* value)
	{
		return context->ClearBufferfv(buffer, drawbuffer, value);
	}

	GLCOREAPI void APIENTRY glClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint* value)
	{
		return context->ClearBufferiv(buffer, drawbuffer, value);
	}

	GLCOREAPI void APIENTRY glClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint* value)
	{
		return context->ClearBufferuiv(buffer, drawbuffer, value);
	}

	GLCOREAPI void APIENTRY glClearDepthf(GLfloat d)
	{
		return context->ClearDepthf(d);
	}

	GLCOREAPI void APIENTRY glClearNamedBufferData(GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void* data)
	{
		return context->ClearNamedBufferData(buffer, internalformat, format, type, data);
	}

	GLCOREAPI void APIENTRY glClearNamedBufferSubData(GLuint buffer, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void* data)
	{
		return context->ClearNamedBufferSubData(buffer, internalformat, offset, size, format, type, data);
	}

	GLCOREAPI void APIENTRY glClearNamedFramebufferfi(GLuint framebuffer, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil)
	{
		return context->ClearNamedFramebufferfi(framebuffer, buffer, drawbuffer, depth, stencil);
	}

	GLCOREAPI void APIENTRY glClearNamedFramebufferfv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat* value)
	{
		return context->ClearNamedFramebufferfv(framebuffer, buffer, drawbuffer, value);
	}

	GLCOREAPI void APIENTRY glClearNamedFramebufferiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint* value)
	{
		return context->ClearNamedFramebufferiv(framebuffer, buffer, drawbuffer, value);
	}

	GLCOREAPI void APIENTRY glClearNamedFramebufferuiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint* value)
	{
		return context->ClearNamedFramebufferuiv(framebuffer, buffer, drawbuffer, value);
	}

	GLCOREAPI void APIENTRY glClearTexImage(GLuint texture, GLint level, GLenum format, GLenum type, const void* data)
	{
		return context->ClearTexImage(texture, level, format, type, data);
	}

	GLCOREAPI void APIENTRY glClearTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* data)
	{
		return context->ClearTexSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, data);
	}

	GLCOREAPI GLenum APIENTRY glClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout)
	{
		return context->ClientWaitSync(sync, flags, timeout);
	}

	GLCOREAPI void APIENTRY glClipControl(GLenum origin, GLenum depth)
	{
		return context->ClipControl(origin, depth);
	}

	GLCOREAPI void APIENTRY glColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a)
	{
		return context->ColorMaski(index, r, g, b, a);
	}

	GLCOREAPI void APIENTRY glCompileShader(GLuint shader)
	{
		return context->CompileShader(shader);
	}

	GLCOREAPI void APIENTRY glCompressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void* data)
	{
		return context->CompressedTexImage1D(target, level, internalformat, width, border, imageSize, data);
	}

	GLCOREAPI void APIENTRY glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data)
	{
		return context->CompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
	}

	GLCOREAPI void APIENTRY glCompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void* data)
	{
		return context->CompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data);
	}

	GLCOREAPI void APIENTRY glCompressedTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void* data)
	{
		return context->CompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data);
	}

	GLCOREAPI void APIENTRY glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data)
	{
		return context->CompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
	}

	GLCOREAPI void APIENTRY glCompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void* data)
	{
		return context->CompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
	}

	GLCOREAPI void APIENTRY glCompressedTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void* data)
	{
		return context->CompressedTextureSubImage1D(texture, level, xoffset, width, format, imageSize, data);
	}

	GLCOREAPI void APIENTRY glCompressedTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data)
	{
		return context->CompressedTextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, imageSize, data);
	}

	GLCOREAPI void APIENTRY glCompressedTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void* data)
	{
		return context->CompressedTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
	}

	GLCOREAPI void APIENTRY glCopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
	{
		return context->CopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size);
	}

	GLCOREAPI void APIENTRY glCopyImageSubData(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth)
	{
		return context->CopyImageSubData(srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth);
	}

	GLCOREAPI void APIENTRY glCopyNamedBufferSubData(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
	{
		return context->CopyNamedBufferSubData(readBuffer, writeBuffer, readOffset, writeOffset, size);
	}

	GLCOREAPI void APIENTRY glCopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
	{
		return context->CopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
	}

	GLCOREAPI void APIENTRY glCopyTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width)
	{
		return context->CopyTextureSubImage1D(texture, level, xoffset, x, y, width);
	}

	GLCOREAPI void APIENTRY glCopyTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
	{
		return context->CopyTextureSubImage2D(texture, level, xoffset, yoffset, x, y, width, height);
	}

	GLCOREAPI void APIENTRY glCopyTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
	{
		return context->CopyTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, x, y, width, height);
	}

	GLCOREAPI void APIENTRY glCreateBuffers(GLsizei n, GLuint* buffers)
	{
		return context->CreateBuffers(n, buffers);
	}

	GLCOREAPI void APIENTRY glCreateFramebuffers(GLsizei n, GLuint* framebuffers)
	{
		return context->CreateFramebuffers(n, framebuffers);
	}

	GLCOREAPI GLuint APIENTRY glCreateProgram()
	{
		return context->CreateProgram();
	}

	GLCOREAPI void APIENTRY glCreateProgramPipelines(GLsizei n, GLuint* pipelines)
	{
		return context->CreateProgramPipelines(n, pipelines);
	}

	GLCOREAPI void APIENTRY glCreateQueries(GLenum target, GLsizei n, GLuint* ids)
	{
		return context->CreateQueries(target, n, ids);
	}

	GLCOREAPI void APIENTRY glCreateRenderbuffers(GLsizei n, GLuint* renderbuffers)
	{
		return context->CreateRenderbuffers(n, renderbuffers);
	}

	GLCOREAPI void APIENTRY glCreateSamplers(GLsizei n, GLuint* samplers)
	{
		return context->CreateSamplers(n, samplers);
	}

	GLCOREAPI GLuint APIENTRY glCreateShader(GLenum type)
	{
		return context->CreateShader(type);
	}

	GLCOREAPI GLuint APIENTRY glCreateShaderProgramv(GLenum type, GLsizei count, const GLchar* const* strings)
	{
		return context->CreateShaderProgramv(type, count, strings);
	}

	GLCOREAPI void APIENTRY glCreateTextures(GLenum target, GLsizei n, GLuint* textures)
	{
		return context->CreateTextures(target, n, textures);
	}

	GLCOREAPI void APIENTRY glCreateTransformFeedbacks(GLsizei n, GLuint* ids)
	{
		return context->CreateTransformFeedbacks(n, ids);
	}

	GLCOREAPI void APIENTRY glCreateVertexArrays(GLsizei n, GLuint* arrays)
	{
		return context->CreateVertexArrays(n, arrays);
	}

	GLCOREAPI void APIENTRY glDebugMessageCallback(GLDEBUGPROC callback, const void* userParam)
	{
		return context->DebugMessageCallback(callback, userParam);
	}

	GLCOREAPI void APIENTRY glDebugMessageControl(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint* ids, GLboolean enabled)
	{
		return context->DebugMessageControl(source, type, severity, count, ids, enabled);
	}

	GLCOREAPI void APIENTRY glDebugMessageInsert(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* buf)
	{
		return context->DebugMessageInsert(source, type, id, severity, length, buf);
	}

	GLCOREAPI void APIENTRY glDeleteBuffers(GLsizei n, const GLuint* buffers)
	{
		return context->DeleteBuffers(n, buffers);
	}

	GLCOREAPI void APIENTRY glDeleteFramebuffers(GLsizei n, const GLuint* framebuffers)
	{
		return context->DeleteFramebuffers(n, framebuffers);
	}

	GLCOREAPI void APIENTRY glDeleteProgram(GLuint program)
	{
		return context->DeleteProgram(program);
	}

	GLCOREAPI void APIENTRY glDeleteProgramPipelines(GLsizei n, const GLuint* pipelines)
	{
		return context->DeleteProgramPipelines(n, pipelines);
	}

	GLCOREAPI void APIENTRY glDeleteQueries(GLsizei n, const GLuint* ids)
	{
		return context->DeleteQueries(n, ids);
	}

	GLCOREAPI void APIENTRY glDeleteRenderbuffers(GLsizei n, const GLuint* renderbuffers)
	{
		return context->DeleteRenderbuffers(n, renderbuffers);
	}

	GLCOREAPI void APIENTRY glDeleteSamplers(GLsizei count, const GLuint* samplers)
	{
		return context->DeleteSamplers(count, samplers);
	}

	GLCOREAPI void APIENTRY glDeleteShader(GLuint shader)
	{
		return context->DeleteShader(shader);
	}

	GLCOREAPI void APIENTRY glDeleteSync(GLsync sync)
	{
		return context->DeleteSync(sync);
	}

	GLCOREAPI void APIENTRY glDeleteTransformFeedbacks(GLsizei n, const GLuint* ids)
	{
		return context->DeleteTransformFeedbacks(n, ids);
	}

	GLCOREAPI void APIENTRY glDeleteVertexArrays(GLsizei n, const GLuint* arrays)
	{
		return context->DeleteVertexArrays(n, arrays);
	}

	GLCOREAPI void APIENTRY glDepthRangeArrayv(GLuint first, GLsizei count, const GLdouble* v)
	{
		return context->DepthRangeArrayv(first, count, v);
	}

	GLCOREAPI void APIENTRY glDepthRangeIndexed(GLuint index, GLdouble n, GLdouble f)
	{
		return context->DepthRangeIndexed(index, n, f);
	}

	GLCOREAPI void APIENTRY glDepthRangef(GLfloat n, GLfloat f)
	{
		return context->DepthRangef(n, f);
	}

	GLCOREAPI void APIENTRY glDetachShader(GLuint program, GLuint shader)
	{
		return context->DetachShader(program, shader);
	}

	GLCOREAPI void APIENTRY glDisableVertexArrayAttrib(GLuint vaobj, GLuint index)
	{
		return context->DisableVertexArrayAttrib(vaobj, index);
	}

	GLCOREAPI void APIENTRY glDisableVertexAttribArray(GLuint index)
	{
		return context->DisableVertexAttribArray(index);
	}

	GLCOREAPI void APIENTRY glDisablei(GLenum target, GLuint index)
	{
		return context->Disablei(target, index);
	}

	GLCOREAPI void APIENTRY glDispatchCompute(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z)
	{
		return context->DispatchCompute(num_groups_x, num_groups_y, num_groups_z);
	}

	GLCOREAPI void APIENTRY glDispatchComputeIndirect(GLintptr indirect)
	{
		return context->DispatchComputeIndirect(indirect);
	}

	GLCOREAPI void APIENTRY glDrawArraysIndirect(GLenum mode, const void* indirect)
	{
		return context->DrawArraysIndirect(mode, indirect);
	}

	GLCOREAPI void APIENTRY glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount)
	{
		return context->DrawArraysInstanced(mode, first, count, instancecount);
	}

	GLCOREAPI void APIENTRY glDrawArraysInstancedBaseInstance(GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance)
	{
		return context->DrawArraysInstancedBaseInstance(mode, first, count, instancecount, baseinstance);
	}

	GLCOREAPI void APIENTRY glDrawBuffers(GLsizei n, const GLenum* bufs)
	{
		return context->DrawBuffers(n, bufs);
	}

	GLCOREAPI void APIENTRY glDrawElementsBaseVertex(GLenum mode, GLsizei count, GLenum type, const void* indices, GLint basevertex)
	{
		return context->DrawElementsBaseVertex(mode, count, type, indices, basevertex);
	}

	GLCOREAPI void APIENTRY glDrawElementsIndirect(GLenum mode, GLenum type, const void* indirect)
	{
		return context->DrawElementsIndirect(mode, type, indirect);
	}

	GLCOREAPI void APIENTRY glDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount)
	{
		return context->DrawElementsInstanced(mode, count, type, indices, instancecount);
	}

	GLCOREAPI void APIENTRY glDrawElementsInstancedBaseInstance(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount, GLuint baseinstance)
	{
		return context->DrawElementsInstancedBaseInstance(mode, count, type, indices, instancecount, baseinstance);
	}

	GLCOREAPI void APIENTRY glDrawElementsInstancedBaseVertex(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount, GLint basevertex)
	{
		return context->DrawElementsInstancedBaseVertex(mode, count, type, indices, instancecount, basevertex);
	}

	GLCOREAPI void APIENTRY glDrawElementsInstancedBaseVertexBaseInstance(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance)
	{
		return context->DrawElementsInstancedBaseVertexBaseInstance(mode, count, type, indices, instancecount, basevertex, baseinstance);
	}

	GLCOREAPI void APIENTRY glDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void* indices)
	{
		return context->DrawRangeElements(mode, start, end, count, type, indices);
	}

	GLCOREAPI void APIENTRY glDrawRangeElementsBaseVertex(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void* indices, GLint basevertex)
	{
		return context->DrawRangeElementsBaseVertex(mode, start, end, count, type, indices, basevertex);
	}

	GLCOREAPI void APIENTRY glDrawTransformFeedback(GLenum mode, GLuint id)
	{
		return context->DrawTransformFeedback(mode, id);
	}

	GLCOREAPI void APIENTRY glDrawTransformFeedbackInstanced(GLenum mode, GLuint id, GLsizei instancecount)
	{
		return context->DrawTransformFeedbackInstanced(mode, id, instancecount);
	}

	GLCOREAPI void APIENTRY glDrawTransformFeedbackStream(GLenum mode, GLuint id, GLuint stream)
	{
		return context->DrawTransformFeedbackStream(mode, id, stream);
	}

	GLCOREAPI void APIENTRY glDrawTransformFeedbackStreamInstanced(GLenum mode, GLuint id, GLuint stream, GLsizei instancecount)
	{
		return context->DrawTransformFeedbackStreamInstanced(mode, id, stream, instancecount);
	}

	GLCOREAPI void APIENTRY glEnableVertexArrayAttrib(GLuint vaobj, GLuint index)
	{
		return context->EnableVertexArrayAttrib(vaobj, index);
	}

	GLCOREAPI void APIENTRY glEnableVertexAttribArray(GLuint index)
	{
		return context->EnableVertexAttribArray(index);
	}

	GLCOREAPI void APIENTRY glEnablei(GLenum target, GLuint index)
	{
		return context->Enablei(target, index);
	}

	GLCOREAPI void APIENTRY glEndConditionalRender()
	{
		return context->EndConditionalRender();
	}

	GLCOREAPI void APIENTRY glEndQuery(GLenum target)
	{
		return context->EndQuery(target);
	}

	GLCOREAPI void APIENTRY glEndQueryIndexed(GLenum target, GLuint index)
	{
		return context->EndQueryIndexed(target, index);
	}

	GLCOREAPI void APIENTRY glEndTransformFeedback()
	{
		return context->EndTransformFeedback();
	}

	GLCOREAPI GLsync APIENTRY glFenceSync(GLenum condition, GLbitfield flags)
	{
		return context->FenceSync(condition, flags);
	}

	GLCOREAPI void APIENTRY glFlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length)
	{
		return context->FlushMappedBufferRange(target, offset, length);
	}

	GLCOREAPI void APIENTRY glFlushMappedNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length)
	{
		return context->FlushMappedNamedBufferRange(buffer, offset, length);
	}

	GLCOREAPI void APIENTRY glFramebufferParameteri(GLenum target, GLenum pname, GLint param)
	{
		return context->FramebufferParameteri(target, pname, param);
	}

	GLCOREAPI void APIENTRY glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
	{
		return context->FramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
	}

	GLCOREAPI void APIENTRY glFramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level)
	{
		return context->FramebufferTexture(target, attachment, texture, level);
	}

	GLCOREAPI void APIENTRY glFramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
	{
		return context->FramebufferTexture1D(target, attachment, textarget, texture, level);
	}

	GLCOREAPI void APIENTRY glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
	{
		return context->FramebufferTexture2D(target, attachment, textarget, texture, level);
	}

	GLCOREAPI void APIENTRY glFramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset)
	{
		return context->FramebufferTexture3D(target, attachment, textarget, texture, level, zoffset);
	}

	GLCOREAPI void APIENTRY glFramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer)
	{
		return context->FramebufferTextureLayer(target, attachment, texture, level, layer);
	}

	GLCOREAPI void APIENTRY glGenBuffers(GLsizei n, GLuint* buffers)
	{
		return context->GenBuffers(n, buffers);
	}

	GLCOREAPI void APIENTRY glGenFramebuffers(GLsizei n, GLuint* framebuffers)
	{
		return context->GenFramebuffers(n, framebuffers);
	}

	GLCOREAPI void APIENTRY glGenProgramPipelines(GLsizei n, GLuint* pipelines)
	{
		return context->GenProgramPipelines(n, pipelines);
	}

	GLCOREAPI void APIENTRY glGenQueries(GLsizei n, GLuint* ids)
	{
		return context->GenQueries(n, ids);
	}

	GLCOREAPI void APIENTRY glGenRenderbuffers(GLsizei n, GLuint* renderbuffers)
	{
		return context->GenRenderbuffers(n, renderbuffers);
	}

	GLCOREAPI void APIENTRY glGenSamplers(GLsizei count, GLuint* samplers)
	{
		return context->GenSamplers(count, samplers);
	}

	GLCOREAPI void APIENTRY glGenTransformFeedbacks(GLsizei n, GLuint* ids)
	{
		return context->GenTransformFeedbacks(n, ids);
	}

	GLCOREAPI void APIENTRY glGenVertexArrays(GLsizei n, GLuint* arrays)
	{
		return context->GenVertexArrays(n, arrays);
	}

	GLCOREAPI void APIENTRY glGenerateMipmap(GLenum target)
	{
		return context->GenerateMipmap(target);
	}

	GLCOREAPI void APIENTRY glGenerateTextureMipmap(GLuint texture)
	{
		return context->GenerateTextureMipmap(texture);
	}

	GLCOREAPI void APIENTRY glGetActiveAtomicCounterBufferiv(GLuint program, GLuint bufferIndex, GLenum pname, GLint* params)
	{
		return context->GetActiveAtomicCounterBufferiv(program, bufferIndex, pname, params);
	}

	GLCOREAPI void APIENTRY glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name)
	{
		return context->GetActiveAttrib(program, index, bufSize, length, size, type, name);
	}

	GLCOREAPI void APIENTRY glGetActiveSubroutineName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei* length, GLchar* name)
	{
		return context->GetActiveSubroutineName(program, shadertype, index, bufsize, length, name);
	}

	GLCOREAPI void APIENTRY glGetActiveSubroutineUniformName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei* length, GLchar* name)
	{
		return context->GetActiveSubroutineUniformName(program, shadertype, index, bufsize, length, name);
	}

	GLCOREAPI void APIENTRY glGetActiveSubroutineUniformiv(GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint* values)
	{
		return context->GetActiveSubroutineUniformiv(program, shadertype, index, pname, values);
	}

	GLCOREAPI void APIENTRY glGetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name)
	{
		return context->GetActiveUniform(program, index, bufSize, length, size, type, name);
	}

	GLCOREAPI void APIENTRY glGetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformBlockName)
	{
		return context->GetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, uniformBlockName);
	}

	GLCOREAPI void APIENTRY glGetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint* params)
	{
		return context->GetActiveUniformBlockiv(program, uniformBlockIndex, pname, params);
	}

	GLCOREAPI void APIENTRY glGetActiveUniformName(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformName)
	{
		return context->GetActiveUniformName(program, uniformIndex, bufSize, length, uniformName);
	}

	GLCOREAPI void APIENTRY glGetActiveUniformsiv(GLuint program, GLsizei uniformCount, const GLuint* uniformIndices, GLenum pname, GLint* params)
	{
		return context->GetActiveUniformsiv(program, uniformCount, uniformIndices, pname, params);
	}

	GLCOREAPI void APIENTRY glGetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei* count, GLuint* shaders)
	{
		return context->GetAttachedShaders(program, maxCount, count, shaders);
	}

	GLCOREAPI GLint APIENTRY glGetAttribLocation(GLuint program, const GLchar* name)
	{
		return context->GetAttribLocation(program, name);
	}

	GLCOREAPI void APIENTRY glGetBooleani_v(GLenum target, GLuint index, GLboolean* data)
	{
		return context->GetBooleani_v(target, index, data);
	}

	GLCOREAPI void APIENTRY glGetBufferParameteri64v(GLenum target, GLenum pname, GLint64* params)
	{
		return context->GetBufferParameteri64v(target, pname, params);
	}

	GLCOREAPI void APIENTRY glGetBufferParameteriv(GLenum target, GLenum pname, GLint* params)
	{
		return context->GetBufferParameteriv(target, pname, params);
	}

	GLCOREAPI void APIENTRY glGetBufferPointerv(GLenum target, GLenum pname, void** params)
	{
		return context->GetBufferPointerv(target, pname, params);
	}

	GLCOREAPI void APIENTRY glGetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, void* data)
	{
		return context->GetBufferSubData(target, offset, size, data);
	}

	GLCOREAPI void APIENTRY glGetCompressedTexImage(GLenum target, GLint level, void* img)
	{
		return context->GetCompressedTexImage(target, level, img);
	}

	GLCOREAPI void APIENTRY glGetCompressedTextureImage(GLuint texture, GLint level, GLsizei bufSize, void* pixels)
	{
		return context->GetCompressedTextureImage(texture, level, bufSize, pixels);
	}

	GLCOREAPI void APIENTRY glGetCompressedTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, void* pixels)
	{
		return context->GetCompressedTextureSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, bufSize, pixels);
	}

	GLCOREAPI GLuint APIENTRY glGetDebugMessageLog(GLuint count, GLsizei bufSize, GLenum* sources, GLenum* types, GLuint* ids, GLenum* severities, GLsizei* lengths, GLchar* messageLog)
	{
		return context->GetDebugMessageLog(count, bufSize, sources, types, ids, severities, lengths, messageLog);
	}

	GLCOREAPI void APIENTRY glGetDoublei_v(GLenum target, GLuint index, GLdouble* data)
	{
		return context->GetDoublei_v(target, index, data);
	}

	GLCOREAPI void APIENTRY glGetFloati_v(GLenum target, GLuint index, GLfloat* data)
	{
		return context->GetFloati_v(target, index, data);
	}

	GLCOREAPI GLint APIENTRY glGetFragDataIndex(GLuint program, const GLchar* name)
	{
		return context->GetFragDataIndex(program, name);
	}

	GLCOREAPI GLint APIENTRY glGetFragDataLocation(GLuint program, const GLchar* name)
	{
		return context->GetFragDataLocation(program, name);
	}

	GLCOREAPI void APIENTRY glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint* params)
	{
		return context->GetFramebufferAttachmentParameteriv(target, attachment, pname, params);
	}

	GLCOREAPI void APIENTRY glGetFramebufferParameteriv(GLenum target, GLenum pname, GLint* params)
	{
		return context->GetFramebufferParameteriv(target, pname, params);
	}

	GLCOREAPI GLenum APIENTRY glGetGraphicsResetStatus()
	{
		return context->GetGraphicsResetStatus();
	}

	GLCOREAPI void APIENTRY glGetInteger64i_v(GLenum target, GLuint index, GLint64* data)
	{
		return context->GetInteger64i_v(target, index, data);
	}

	GLCOREAPI void APIENTRY glGetInteger64v(GLenum pname, GLint64* data)
	{
		return context->GetInteger64v(pname, data);
	}

	GLCOREAPI void APIENTRY glGetIntegeri_v(GLenum target, GLuint index, GLint* data)
	{
		return context->GetIntegeri_v(target, index, data);
	}

	GLCOREAPI void APIENTRY glGetInternalformati64v(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint64* params)
	{
		return context->GetInternalformati64v(target, internalformat, pname, bufSize, params);
	}

	GLCOREAPI void APIENTRY glGetInternalformativ(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint* params)
	{
		return context->GetInternalformativ(target, internalformat, pname, bufSize, params);
	}

	GLCOREAPI void APIENTRY glGetMultisamplefv(GLenum pname, GLuint index, GLfloat* val)
	{
		return context->GetMultisamplefv(pname, index, val);
	}

	GLCOREAPI void APIENTRY glGetNamedBufferParameteri64v(GLuint buffer, GLenum pname, GLint64* params)
	{
		return context->GetNamedBufferParameteri64v(buffer, pname, params);
	}

	GLCOREAPI void APIENTRY glGetNamedBufferParameteriv(GLuint buffer, GLenum pname, GLint* params)
	{
		return context->GetNamedBufferParameteriv(buffer, pname, params);
	}

	GLCOREAPI void APIENTRY glGetNamedBufferPointerv(GLuint buffer, GLenum pname, void** params)
	{
		return context->GetNamedBufferPointerv(buffer, pname, params);
	}

	GLCOREAPI void APIENTRY glGetNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, void* data)
	{
		return context->GetNamedBufferSubData(buffer, offset, size, data);
	}

	GLCOREAPI void APIENTRY glGetNamedFramebufferAttachmentParameteriv(GLuint framebuffer, GLenum attachment, GLenum pname, GLint* params)
	{
		return context->GetNamedFramebufferAttachmentParameteriv(framebuffer, attachment, pname, params);
	}

	GLCOREAPI void APIENTRY glGetNamedFramebufferParameteriv(GLuint framebuffer, GLenum pname, GLint* param)
	{
		return context->GetNamedFramebufferParameteriv(framebuffer, pname, param);
	}

	GLCOREAPI void APIENTRY glGetNamedRenderbufferParameteriv(GLuint renderbuffer, GLenum pname, GLint* params)
	{
		return context->GetNamedRenderbufferParameteriv(renderbuffer, pname, params);
	}

	GLCOREAPI void APIENTRY glGetObjectLabel(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei* length, GLchar* label)
	{
		return context->GetObjectLabel(identifier, name, bufSize, length, label);
	}

	GLCOREAPI void APIENTRY glGetObjectPtrLabel(const void* ptr, GLsizei bufSize, GLsizei* length, GLchar* label)
	{
		return context->GetObjectPtrLabel(ptr, bufSize, length, label);
	}

	GLCOREAPI void APIENTRY glGetProgramBinary(GLuint program, GLsizei bufSize, GLsizei* length, GLenum* binaryFormat, void* binary)
	{
		return context->GetProgramBinary(program, bufSize, length, binaryFormat, binary);
	}

	GLCOREAPI void APIENTRY glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog)
	{
		return context->GetProgramInfoLog(program, bufSize, length, infoLog);
	}

	GLCOREAPI void APIENTRY glGetProgramInterfaceiv(GLuint program, GLenum programInterface, GLenum pname, GLint* params)
	{
		return context->GetProgramInterfaceiv(program, programInterface, pname, params);
	}

	GLCOREAPI void APIENTRY glGetProgramPipelineInfoLog(GLuint pipeline, GLsizei bufSize, GLsizei* length, GLchar* infoLog)
	{
		return context->GetProgramPipelineInfoLog(pipeline, bufSize, length, infoLog);
	}

	GLCOREAPI void APIENTRY glGetProgramPipelineiv(GLuint pipeline, GLenum pname, GLint* params)
	{
		return context->GetProgramPipelineiv(pipeline, pname, params);
	}

	GLCOREAPI GLuint APIENTRY glGetProgramResourceIndex(GLuint program, GLenum programInterface, const GLchar* name)
	{
		return context->GetProgramResourceIndex(program, programInterface, name);
	}

	GLCOREAPI GLint APIENTRY glGetProgramResourceLocation(GLuint program, GLenum programInterface, const GLchar* name)
	{
		return context->GetProgramResourceLocation(program, programInterface, name);
	}

	GLCOREAPI GLint APIENTRY glGetProgramResourceLocationIndex(GLuint program, GLenum programInterface, const GLchar* name)
	{
		return context->GetProgramResourceLocationIndex(program, programInterface, name);
	}

	GLCOREAPI void APIENTRY glGetProgramResourceName(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei* length, GLchar* name)
	{
		return context->GetProgramResourceName(program, programInterface, index, bufSize, length, name);
	}

	GLCOREAPI void APIENTRY glGetProgramResourceiv(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum* props, GLsizei bufSize, GLsizei* length, GLint* params)
	{
		return context->GetProgramResourceiv(program, programInterface, index, propCount, props, bufSize, length, params);
	}

	GLCOREAPI void APIENTRY glGetProgramStageiv(GLuint program, GLenum shadertype, GLenum pname, GLint* values)
	{
		return context->GetProgramStageiv(program, shadertype, pname, values);
	}

	GLCOREAPI void APIENTRY glGetProgramiv(GLuint program, GLenum pname, GLint* params)
	{
		return context->GetProgramiv(program, pname, params);
	}

	GLCOREAPI void APIENTRY glGetQueryBufferObjecti64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset)
	{
		return context->GetQueryBufferObjecti64v(id, buffer, pname, offset);
	}

	GLCOREAPI void APIENTRY glGetQueryBufferObjectiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset)
	{
		return context->GetQueryBufferObjectiv(id, buffer, pname, offset);
	}

	GLCOREAPI void APIENTRY glGetQueryBufferObjectui64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset)
	{
		return context->GetQueryBufferObjectui64v(id, buffer, pname, offset);
	}

	GLCOREAPI void APIENTRY glGetQueryBufferObjectuiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset)
	{
		return context->GetQueryBufferObjectuiv(id, buffer, pname, offset);
	}

	GLCOREAPI void APIENTRY glGetQueryIndexediv(GLenum target, GLuint index, GLenum pname, GLint* params)
	{
		return context->GetQueryIndexediv(target, index, pname, params);
	}

	GLCOREAPI void APIENTRY glGetQueryObjecti64v(GLuint id, GLenum pname, GLint64* params)
	{
		return context->GetQueryObjecti64v(id, pname, params);
	}

	GLCOREAPI void APIENTRY glGetQueryObjectiv(GLuint id, GLenum pname, GLint* params)
	{
		return context->GetQueryObjectiv(id, pname, params);
	}

	GLCOREAPI void APIENTRY glGetQueryObjectui64v(GLuint id, GLenum pname, GLuint64* params)
	{
		return context->GetQueryObjectui64v(id, pname, params);
	}

	GLCOREAPI void APIENTRY glGetQueryObjectuiv(GLuint id, GLenum pname, GLuint* params)
	{
		return context->GetQueryObjectuiv(id, pname, params);
	}

	GLCOREAPI void APIENTRY glGetQueryiv(GLenum target, GLenum pname, GLint* params)
	{
		return context->GetQueryiv(target, pname, params);
	}

	GLCOREAPI void APIENTRY glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint* params)
	{
		return context->GetRenderbufferParameteriv(target, pname, params);
	}

	GLCOREAPI void APIENTRY glGetSamplerParameterIiv(GLuint sampler, GLenum pname, GLint* params)
	{
		return context->GetSamplerParameterIiv(sampler, pname, params);
	}

	GLCOREAPI void APIENTRY glGetSamplerParameterIuiv(GLuint sampler, GLenum pname, GLuint* params)
	{
		return context->GetSamplerParameterIuiv(sampler, pname, params);
	}

	GLCOREAPI void APIENTRY glGetSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat* params)
	{
		return context->GetSamplerParameterfv(sampler, pname, params);
	}

	GLCOREAPI void APIENTRY glGetSamplerParameteriv(GLuint sampler, GLenum pname, GLint* params)
	{
		return context->GetSamplerParameteriv(sampler, pname, params);
	}

	GLCOREAPI void APIENTRY glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog)
	{
		return context->GetShaderInfoLog(shader, bufSize, length, infoLog);
	}

	GLCOREAPI void APIENTRY glGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision)
	{
		return context->GetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
	}

	GLCOREAPI void APIENTRY glGetShaderSource(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* source)
	{
		return context->GetShaderSource(shader, bufSize, length, source);
	}

	GLCOREAPI void APIENTRY glGetShaderiv(GLuint shader, GLenum pname, GLint* params)
	{
		return context->GetShaderiv(shader, pname, params);
	}

	GLCOREAPI const GLubyte* APIENTRY glGetStringi(GLenum name, GLuint index)
	{
		return context->GetStringi(name, index);
	}

	GLCOREAPI GLuint APIENTRY glGetSubroutineIndex(GLuint program, GLenum shadertype, const GLchar* name)
	{
		return context->GetSubroutineIndex(program, shadertype, name);
	}

	GLCOREAPI GLint APIENTRY glGetSubroutineUniformLocation(GLuint program, GLenum shadertype, const GLchar* name)
	{
		return context->GetSubroutineUniformLocation(program, shadertype, name);
	}

	GLCOREAPI void APIENTRY glGetSynciv(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei* length, GLint* values)
	{
		return context->GetSynciv(sync, pname, bufSize, length, values);
	}

	GLCOREAPI void APIENTRY glGetTexParameterIiv(GLenum target, GLenum pname, GLint* params)
	{
		return context->GetTexParameterIiv(target, pname, params);
	}

	GLCOREAPI void APIENTRY glGetTexParameterIuiv(GLenum target, GLenum pname, GLuint* params)
	{
		return context->GetTexParameterIuiv(target, pname, params);
	}

	GLCOREAPI void APIENTRY glGetTextureImage(GLuint texture, GLint level, GLenum format, GLenum type, GLsizei bufSize, void* pixels)
	{
		return context->GetTextureImage(texture, level, format, type, bufSize, pixels);
	}

	GLCOREAPI void APIENTRY glGetTextureLevelParameterfv(GLuint texture, GLint level, GLenum pname, GLfloat* params)
	{
		return context->GetTextureLevelParameterfv(texture, level, pname, params);
	}

	GLCOREAPI void APIENTRY glGetTextureLevelParameteriv(GLuint texture, GLint level, GLenum pname, GLint* params)
	{
		return context->GetTextureLevelParameteriv(texture, level, pname, params);
	}

	GLCOREAPI void APIENTRY glGetTextureParameterIiv(GLuint texture, GLenum pname, GLint* params)
	{
		return context->GetTextureParameterIiv(texture, pname, params);
	}

	GLCOREAPI void APIENTRY glGetTextureParameterIuiv(GLuint texture, GLenum pname, GLuint* params)
	{
		return context->GetTextureParameterIuiv(texture, pname, params);
	}

	GLCOREAPI void APIENTRY glGetTextureParameterfv(GLuint texture, GLenum pname, GLfloat* params)
	{
		return context->GetTextureParameterfv(texture, pname, params);
	}

	GLCOREAPI void APIENTRY glGetTextureParameteriv(GLuint texture, GLenum pname, GLint* params)
	{
		return context->GetTextureParameteriv(texture, pname, params);
	}

	GLCOREAPI void APIENTRY glGetTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void* pixels)
	{
		return context->GetTextureSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, bufSize, pixels);
	}

	GLCOREAPI void APIENTRY glGetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLsizei* size, GLenum* type, GLchar* name)
	{
		return context->GetTransformFeedbackVarying(program, index, bufSize, length, size, type, name);
	}

	GLCOREAPI void APIENTRY glGetTransformFeedbacki64_v(GLuint xfb, GLenum pname, GLuint index, GLint64* param)
	{
		return context->GetTransformFeedbacki64_v(xfb, pname, index, param);
	}

	GLCOREAPI void APIENTRY glGetTransformFeedbacki_v(GLuint xfb, GLenum pname, GLuint index, GLint* param)
	{
		return context->GetTransformFeedbacki_v(xfb, pname, index, param);
	}

	GLCOREAPI void APIENTRY glGetTransformFeedbackiv(GLuint xfb, GLenum pname, GLint* param)
	{
		return context->GetTransformFeedbackiv(xfb, pname, param);
	}

	GLCOREAPI GLuint APIENTRY glGetUniformBlockIndex(GLuint program, const GLchar* uniformBlockName)
	{
		return context->GetUniformBlockIndex(program, uniformBlockName);
	}

	GLCOREAPI void APIENTRY glGetUniformIndices(GLuint program, GLsizei uniformCount, const GLchar* const* uniformNames, GLuint* uniformIndices)
	{
		return context->GetUniformIndices(program, uniformCount, uniformNames, uniformIndices);
	}

	GLCOREAPI GLint APIENTRY glGetUniformLocation(GLuint program, const GLchar* name)
	{
		return context->GetUniformLocation(program, name);
	}

	GLCOREAPI void APIENTRY glGetUniformSubroutineuiv(GLenum shadertype, GLint location, GLuint* params)
	{
		return context->GetUniformSubroutineuiv(shadertype, location, params);
	}

	GLCOREAPI void APIENTRY glGetUniformdv(GLuint program, GLint location, GLdouble* params)
	{
		return context->GetUniformdv(program, location, params);
	}

	GLCOREAPI void APIENTRY glGetUniformfv(GLuint program, GLint location, GLfloat* params)
	{
		return context->GetUniformfv(program, location, params);
	}

	GLCOREAPI void APIENTRY glGetUniformiv(GLuint program, GLint location, GLint* params)
	{
		return context->GetUniformiv(program, location, params);
	}

	GLCOREAPI void APIENTRY glGetUniformuiv(GLuint program, GLint location, GLuint* params)
	{
		return context->GetUniformuiv(program, location, params);
	}

	GLCOREAPI void APIENTRY glGetVertexArrayIndexed64iv(GLuint vaobj, GLuint index, GLenum pname, GLint64* param)
	{
		return context->GetVertexArrayIndexed64iv(vaobj, index, pname, param);
	}

	GLCOREAPI void APIENTRY glGetVertexArrayIndexediv(GLuint vaobj, GLuint index, GLenum pname, GLint* param)
	{
		return context->GetVertexArrayIndexediv(vaobj, index, pname, param);
	}

	GLCOREAPI void APIENTRY glGetVertexArrayiv(GLuint vaobj, GLenum pname, GLint* param)
	{
		return context->GetVertexArrayiv(vaobj, pname, param);
	}

	GLCOREAPI void APIENTRY glGetVertexAttribIiv(GLuint index, GLenum pname, GLint* params)
	{
		return context->GetVertexAttribIiv(index, pname, params);
	}

	GLCOREAPI void APIENTRY glGetVertexAttribIuiv(GLuint index, GLenum pname, GLuint* params)
	{
		return context->GetVertexAttribIuiv(index, pname, params);
	}

	GLCOREAPI void APIENTRY glGetVertexAttribLdv(GLuint index, GLenum pname, GLdouble* params)
	{
		return context->GetVertexAttribLdv(index, pname, params);
	}

	GLCOREAPI void APIENTRY glGetVertexAttribPointerv(GLuint index, GLenum pname, void** pointer)
	{
		return context->GetVertexAttribPointerv(index, pname, pointer);
	}

	GLCOREAPI void APIENTRY glGetVertexAttribdv(GLuint index, GLenum pname, GLdouble* params)
	{
		return context->GetVertexAttribdv(index, pname, params);
	}

	GLCOREAPI void APIENTRY glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat* params)
	{
		return context->GetVertexAttribfv(index, pname, params);
	}

	GLCOREAPI void APIENTRY glGetVertexAttribiv(GLuint index, GLenum pname, GLint* params)
	{
		return context->GetVertexAttribiv(index, pname, params);
	}

	GLCOREAPI void APIENTRY glGetnCompressedTexImage(GLenum target, GLint lod, GLsizei bufSize, void* pixels)
	{
		return context->GetnCompressedTexImage(target, lod, bufSize, pixels);
	}

	GLCOREAPI void APIENTRY glGetnTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void* pixels)
	{
		return context->GetnTexImage(target, level, format, type, bufSize, pixels);
	}

	GLCOREAPI void APIENTRY glGetnUniformdv(GLuint program, GLint location, GLsizei bufSize, GLdouble* params)
	{
		return context->GetnUniformdv(program, location, bufSize, params);
	}

	GLCOREAPI void APIENTRY glGetnUniformfv(GLuint program, GLint location, GLsizei bufSize, GLfloat* params)
	{
		return context->GetnUniformfv(program, location, bufSize, params);
	}

	GLCOREAPI void APIENTRY glGetnUniformiv(GLuint program, GLint location, GLsizei bufSize, GLint* params)
	{
		return context->GetnUniformiv(program, location, bufSize, params);
	}

	GLCOREAPI void APIENTRY glGetnUniformuiv(GLuint program, GLint location, GLsizei bufSize, GLuint* params)
	{
		return context->GetnUniformuiv(program, location, bufSize, params);
	}

	GLCOREAPI void APIENTRY glInvalidateBufferData(GLuint buffer)
	{
		return context->InvalidateBufferData(buffer);
	}

	GLCOREAPI void APIENTRY glInvalidateBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr length)
	{
		return context->InvalidateBufferSubData(buffer, offset, length);
	}

	GLCOREAPI void APIENTRY glInvalidateFramebuffer(GLenum target, GLsizei numAttachments, const GLenum* attachments)
	{
		return context->InvalidateFramebuffer(target, numAttachments, attachments);
	}

	GLCOREAPI void APIENTRY glInvalidateNamedFramebufferData(GLuint framebuffer, GLsizei numAttachments, const GLenum* attachments)
	{
		return context->InvalidateNamedFramebufferData(framebuffer, numAttachments, attachments);
	}

	GLCOREAPI void APIENTRY glInvalidateNamedFramebufferSubData(GLuint framebuffer, GLsizei numAttachments, const GLenum* attachments, GLint x, GLint y, GLsizei width, GLsizei height)
	{
		return context->InvalidateNamedFramebufferSubData(framebuffer, numAttachments, attachments, x, y, width, height);
	}

	GLCOREAPI void APIENTRY glInvalidateSubFramebuffer(GLenum target, GLsizei numAttachments, const GLenum* attachments, GLint x, GLint y, GLsizei width, GLsizei height)
	{
		return context->InvalidateSubFramebuffer(target, numAttachments, attachments, x, y, width, height);
	}

	GLCOREAPI void APIENTRY glInvalidateTexImage(GLuint texture, GLint level)
	{
		return context->InvalidateTexImage(texture, level);
	}

	GLCOREAPI void APIENTRY glInvalidateTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth)
	{
		return context->InvalidateTexSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth);
	}

	GLCOREAPI GLboolean APIENTRY glIsBuffer(GLuint buffer)
	{
		return context->IsBuffer(buffer);
	}

	GLCOREAPI GLboolean APIENTRY glIsEnabledi(GLenum target, GLuint index)
	{
		return context->IsEnabledi(target, index);
	}

	GLCOREAPI GLboolean APIENTRY glIsFramebuffer(GLuint framebuffer)
	{
		return context->IsFramebuffer(framebuffer);
	}

	GLCOREAPI GLboolean APIENTRY glIsProgram(GLuint program)
	{
		return context->IsProgram(program);
	}

	GLCOREAPI GLboolean APIENTRY glIsProgramPipeline(GLuint pipeline)
	{
		return context->IsProgramPipeline(pipeline);
	}

	GLCOREAPI GLboolean APIENTRY glIsQuery(GLuint id)
	{
		return context->IsQuery(id);
	}

	GLCOREAPI GLboolean APIENTRY glIsRenderbuffer(GLuint renderbuffer)
	{
		return context->IsRenderbuffer(renderbuffer);
	}

	GLCOREAPI GLboolean APIENTRY glIsSampler(GLuint sampler)
	{
		return context->IsSampler(sampler);
	}

	GLCOREAPI GLboolean APIENTRY glIsShader(GLuint shader)
	{
		return context->IsShader(shader);
	}

	GLCOREAPI GLboolean APIENTRY glIsSync(GLsync sync)
	{
		return context->IsSync(sync);
	}

	GLCOREAPI GLboolean APIENTRY glIsTransformFeedback(GLuint id)
	{
		return context->IsTransformFeedback(id);
	}

	GLCOREAPI GLboolean APIENTRY glIsVertexArray(GLuint array)
	{
		return context->IsVertexArray(array);
	}

	GLCOREAPI void APIENTRY glLinkProgram(GLuint program)
	{
		return context->LinkProgram(program);
	}

	GLCOREAPI void* APIENTRY glMapBuffer(GLenum target, GLenum access)
	{
		return context->MapBuffer(target, access);
	}

	GLCOREAPI void* APIENTRY glMapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access)
	{
		return context->MapBufferRange(target, offset, length, access);
	}

	GLCOREAPI void* APIENTRY glMapNamedBuffer(GLuint buffer, GLenum access)
	{
		return context->MapNamedBuffer(buffer, access);
	}

	GLCOREAPI void* APIENTRY glMapNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access)
	{
		return context->MapNamedBufferRange(buffer, offset, length, access);
	}

	GLCOREAPI void APIENTRY glMemoryBarrier(GLbitfield barriers)
	{
		return context->MemoryBarrier(barriers);
	}

	GLCOREAPI void APIENTRY glMemoryBarrierByRegion(GLbitfield barriers)
	{
		return context->MemoryBarrierByRegion(barriers);
	}

	GLCOREAPI void APIENTRY glMinSampleShading(GLfloat value)
	{
		return context->MinSampleShading(value);
	}

	GLCOREAPI void APIENTRY glMultiDrawArrays(GLenum mode, const GLint* first, const GLsizei* count, GLsizei drawcount)
	{
		return context->MultiDrawArrays(mode, first, count, drawcount);
	}

	GLCOREAPI void APIENTRY glMultiDrawArraysIndirect(GLenum mode, const void* indirect, GLsizei drawcount, GLsizei stride)
	{
		return context->MultiDrawArraysIndirect(mode, indirect, drawcount, stride);
	}

	GLCOREAPI void APIENTRY glMultiDrawElements(GLenum mode, const GLsizei* count, GLenum type, const void* const* indices, GLsizei drawcount)
	{
		return context->MultiDrawElements(mode, count, type, indices, drawcount);
	}

	GLCOREAPI void APIENTRY glMultiDrawElementsBaseVertex(GLenum mode, const GLsizei* count, GLenum type, const void* const* indices, GLsizei drawcount, const GLint* basevertex)
	{
		return context->MultiDrawElementsBaseVertex(mode, count, type, indices, drawcount, basevertex);
	}

	GLCOREAPI void APIENTRY glMultiDrawElementsIndirect(GLenum mode, GLenum type, const void* indirect, GLsizei drawcount, GLsizei stride)
	{
		return context->MultiDrawElementsIndirect(mode, type, indirect, drawcount, stride);
	}

	GLCOREAPI void APIENTRY glNamedBufferData(GLuint buffer, GLsizeiptr size, const void* data, GLenum usage)
	{
		return context->NamedBufferData(buffer, size, data, usage);
	}

	GLCOREAPI void APIENTRY glNamedBufferStorage(GLuint buffer, GLsizeiptr size, const void* data, GLbitfield flags)
	{
		return context->NamedBufferStorage(buffer, size, data, flags);
	}

	GLCOREAPI void APIENTRY glNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, const void* data)
	{
		return context->NamedBufferSubData(buffer, offset, size, data);
	}

	GLCOREAPI void APIENTRY glNamedFramebufferDrawBuffer(GLuint framebuffer, GLenum buf)
	{
		return context->NamedFramebufferDrawBuffer(framebuffer, buf);
	}

	GLCOREAPI void APIENTRY glNamedFramebufferDrawBuffers(GLuint framebuffer, GLsizei n, const GLenum* bufs)
	{
		return context->NamedFramebufferDrawBuffers(framebuffer, n, bufs);
	}

	GLCOREAPI void APIENTRY glNamedFramebufferParameteri(GLuint framebuffer, GLenum pname, GLint param)
	{
		return context->NamedFramebufferParameteri(framebuffer, pname, param);
	}

	GLCOREAPI void APIENTRY glNamedFramebufferReadBuffer(GLuint framebuffer, GLenum src)
	{
		return context->NamedFramebufferReadBuffer(framebuffer, src);
	}

	GLCOREAPI void APIENTRY glNamedFramebufferRenderbuffer(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
	{
		return context->NamedFramebufferRenderbuffer(framebuffer, attachment, renderbuffertarget, renderbuffer);
	}

	GLCOREAPI void APIENTRY glNamedFramebufferTexture(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level)
	{
		return context->NamedFramebufferTexture(framebuffer, attachment, texture, level);
	}

	GLCOREAPI void APIENTRY glNamedFramebufferTextureLayer(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer)
	{
		return context->NamedFramebufferTextureLayer(framebuffer, attachment, texture, level, layer);
	}

	GLCOREAPI void APIENTRY glNamedRenderbufferStorage(GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height)
	{
		return context->NamedRenderbufferStorage(renderbuffer, internalformat, width, height);
	}

	GLCOREAPI void APIENTRY glNamedRenderbufferStorageMultisample(GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)
	{
		return context->NamedRenderbufferStorageMultisample(renderbuffer, samples, internalformat, width, height);
	}

	GLCOREAPI void APIENTRY glObjectLabel(GLenum identifier, GLuint name, GLsizei length, const GLchar* label)
	{
		return context->ObjectLabel(identifier, name, length, label);
	}

	GLCOREAPI void APIENTRY glObjectPtrLabel(const void* ptr, GLsizei length, const GLchar* label)
	{
		return context->ObjectPtrLabel(ptr, length, label);
	}

	GLCOREAPI void APIENTRY glPatchParameterfv(GLenum pname, const GLfloat* values)
	{
		return context->PatchParameterfv(pname, values);
	}

	GLCOREAPI void APIENTRY glPatchParameteri(GLenum pname, GLint value)
	{
		return context->PatchParameteri(pname, value);
	}

	GLCOREAPI void APIENTRY glPauseTransformFeedback()
	{
		return context->PauseTransformFeedback();
	}

	GLCOREAPI void APIENTRY glPointParameterf(GLenum pname, GLfloat param)
	{
		return context->PointParameterf(pname, param);
	}

	GLCOREAPI void APIENTRY glPointParameterfv(GLenum pname, const GLfloat* params)
	{
		return context->PointParameterfv(pname, params);
	}

	GLCOREAPI void APIENTRY glPointParameteri(GLenum pname, GLint param)
	{
		return context->PointParameteri(pname, param);
	}

	GLCOREAPI void APIENTRY glPointParameteriv(GLenum pname, const GLint* params)
	{
		return context->PointParameteriv(pname, params);
	}

	GLCOREAPI void APIENTRY glPopDebugGroup()
	{
		return context->PopDebugGroup();
	}

	GLCOREAPI void APIENTRY glPrimitiveRestartIndex(GLuint index)
	{
		return context->PrimitiveRestartIndex(index);
	}

	GLCOREAPI void APIENTRY glProgramBinary(GLuint program, GLenum binaryFormat, const void* binary, GLsizei length)
	{
		return context->ProgramBinary(program, binaryFormat, binary, length);
	}

	GLCOREAPI void APIENTRY glProgramParameteri(GLuint program, GLenum pname, GLint value)
	{
		return context->ProgramParameteri(program, pname, value);
	}

	GLCOREAPI void APIENTRY glProgramUniform1d(GLuint program, GLint location, GLdouble v0)
	{
		return context->ProgramUniform1d(program, location, v0);
	}

	GLCOREAPI void APIENTRY glProgramUniform1dv(GLuint program, GLint location, GLsizei count, const GLdouble* value)
	{
		return context->ProgramUniform1dv(program, location, count, value);
	}

	GLCOREAPI void APIENTRY glProgramUniform1f(GLuint program, GLint location, GLfloat v0)
	{
		return context->ProgramUniform1f(program, location, v0);
	}

	GLCOREAPI void APIENTRY glProgramUniform1fv(GLuint program, GLint location, GLsizei count, const GLfloat* value)
	{
		return context->ProgramUniform1fv(program, location, count, value);
	}

	GLCOREAPI void APIENTRY glProgramUniform1i(GLuint program, GLint location, GLint v0)
	{
		return context->ProgramUniform1i(program, location, v0);
	}

	GLCOREAPI void APIENTRY glProgramUniform1iv(GLuint program, GLint location, GLsizei count, const GLint* value)
	{
		return context->ProgramUniform1iv(program, location, count, value);
	}

	GLCOREAPI void APIENTRY glProgramUniform1ui(GLuint program, GLint location, GLuint v0)
	{
		return context->ProgramUniform1ui(program, location, v0);
	}

	GLCOREAPI void APIENTRY glProgramUniform1uiv(GLuint program, GLint location, GLsizei count, const GLuint* value)
	{
		return context->ProgramUniform1uiv(program, location, count, value);
	}

	GLCOREAPI void APIENTRY glProgramUniform2d(GLuint program, GLint location, GLdouble v0, GLdouble v1)
	{
		return context->ProgramUniform2d(program, location, v0, v1);
	}

	GLCOREAPI void APIENTRY glProgramUniform2dv(GLuint program, GLint location, GLsizei count, const GLdouble* value)
	{
		return context->ProgramUniform2dv(program, location, count, value);
	}

	GLCOREAPI void APIENTRY glProgramUniform2f(GLuint program, GLint location, GLfloat v0, GLfloat v1)
	{
		return context->ProgramUniform2f(program, location, v0, v1);
	}

	GLCOREAPI void APIENTRY glProgramUniform2fv(GLuint program, GLint location, GLsizei count, const GLfloat* value)
	{
		return context->ProgramUniform2fv(program, location, count, value);
	}

	GLCOREAPI void APIENTRY glProgramUniform2i(GLuint program, GLint location, GLint v0, GLint v1)
	{
		return context->ProgramUniform2i(program, location, v0, v1);
	}

	GLCOREAPI void APIENTRY glProgramUniform2iv(GLuint program, GLint location, GLsizei count, const GLint* value)
	{
		return context->ProgramUniform2iv(program, location, count, value);
	}

	GLCOREAPI void APIENTRY glProgramUniform2ui(GLuint program, GLint location, GLuint v0, GLuint v1)
	{
		return context->ProgramUniform2ui(program, location, v0, v1);
	}

	GLCOREAPI void APIENTRY glProgramUniform2uiv(GLuint program, GLint location, GLsizei count, const GLuint* value)
	{
		return context->ProgramUniform2uiv(program, location, count, value);
	}

	GLCOREAPI void APIENTRY glProgramUniform3d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2)
	{
		return context->ProgramUniform3d(program, location, v0, v1, v2);
	}

	GLCOREAPI void APIENTRY glProgramUniform3dv(GLuint program, GLint location, GLsizei count, const GLdouble* value)
	{
		return context->ProgramUniform3dv(program, location, count, value);
	}

	GLCOREAPI void APIENTRY glProgramUniform3f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
	{
		return context->ProgramUniform3f(program, location, v0, v1, v2);
	}

	GLCOREAPI void APIENTRY glProgramUniform3fv(GLuint program, GLint location, GLsizei count, const GLfloat* value)
	{
		return context->ProgramUniform3fv(program, location, count, value);
	}

	GLCOREAPI void APIENTRY glProgramUniform3i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2)
	{
		return context->ProgramUniform3i(program, location, v0, v1, v2);
	}

	GLCOREAPI void APIENTRY glProgramUniform3iv(GLuint program, GLint location, GLsizei count, const GLint* value)
	{
		return context->ProgramUniform3iv(program, location, count, value);
	}

	GLCOREAPI void APIENTRY glProgramUniform3ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2)
	{
		return context->ProgramUniform3ui(program, location, v0, v1, v2);
	}

	GLCOREAPI void APIENTRY glProgramUniform3uiv(GLuint program, GLint location, GLsizei count, const GLuint* value)
	{
		return context->ProgramUniform3uiv(program, location, count, value);
	}

	GLCOREAPI void APIENTRY glProgramUniform4d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3)
	{
		return context->ProgramUniform4d(program, location, v0, v1, v2, v3);
	}

	GLCOREAPI void APIENTRY glProgramUniform4dv(GLuint program, GLint location, GLsizei count, const GLdouble* value)
	{
		return context->ProgramUniform4dv(program, location, count, value);
	}

	GLCOREAPI void APIENTRY glProgramUniform4f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
	{
		return context->ProgramUniform4f(program, location, v0, v1, v2, v3);
	}

	GLCOREAPI void APIENTRY glProgramUniform4fv(GLuint program, GLint location, GLsizei count, const GLfloat* value)
	{
		return context->ProgramUniform4fv(program, location, count, value);
	}

	GLCOREAPI void APIENTRY glProgramUniform4i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
	{
		return context->ProgramUniform4i(program, location, v0, v1, v2, v3);
	}

	GLCOREAPI void APIENTRY glProgramUniform4iv(GLuint program, GLint location, GLsizei count, const GLint* value)
	{
		return context->ProgramUniform4iv(program, location, count, value);
	}

	GLCOREAPI void APIENTRY glProgramUniform4ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
	{
		return context->ProgramUniform4ui(program, location, v0, v1, v2, v3);
	}

	GLCOREAPI void APIENTRY glProgramUniform4uiv(GLuint program, GLint location, GLsizei count, const GLuint* value)
	{
		return context->ProgramUniform4uiv(program, location, count, value);
	}

	GLCOREAPI void APIENTRY glProgramUniformMatrix2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
	{
		return context->ProgramUniformMatrix2dv(program, location, count, transpose, value);
	}

	GLCOREAPI void APIENTRY glProgramUniformMatrix2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
	{
		return context->ProgramUniformMatrix2fv(program, location, count, transpose, value);
	}

	GLCOREAPI void APIENTRY glProgramUniformMatrix2x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
	{
		return context->ProgramUniformMatrix2x3dv(program, location, count, transpose, value);
	}

	GLCOREAPI void APIENTRY glProgramUniformMatrix2x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
	{
		return context->ProgramUniformMatrix2x3fv(program, location, count, transpose, value);
	}

	GLCOREAPI void APIENTRY glProgramUniformMatrix2x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
	{
		return context->ProgramUniformMatrix2x4dv(program, location, count, transpose, value);
	}

	GLCOREAPI void APIENTRY glProgramUniformMatrix2x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
	{
		return context->ProgramUniformMatrix2x4fv(program, location, count, transpose, value);
	}

	GLCOREAPI void APIENTRY glProgramUniformMatrix3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
	{
		return context->ProgramUniformMatrix3dv(program, location, count, transpose, value);
	}

	GLCOREAPI void APIENTRY glProgramUniformMatrix3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
	{
		return context->ProgramUniformMatrix3fv(program, location, count, transpose, value);
	}

	GLCOREAPI void APIENTRY glProgramUniformMatrix3x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
	{
		return context->ProgramUniformMatrix3x2dv(program, location, count, transpose, value);
	}

	GLCOREAPI void APIENTRY glProgramUniformMatrix3x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
	{
		return context->ProgramUniformMatrix3x2fv(program, location, count, transpose, value);
	}

	GLCOREAPI void APIENTRY glProgramUniformMatrix3x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
	{
		return context->ProgramUniformMatrix3x4dv(program, location, count, transpose, value);
	}

	GLCOREAPI void APIENTRY glProgramUniformMatrix3x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
	{
		return context->ProgramUniformMatrix3x4fv(program, location, count, transpose, value);
	}

	GLCOREAPI void APIENTRY glProgramUniformMatrix4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
	{
		return context->ProgramUniformMatrix4dv(program, location, count, transpose, value);
	}

	GLCOREAPI void APIENTRY glProgramUniformMatrix4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
	{
		return context->ProgramUniformMatrix4fv(program, location, count, transpose, value);
	}

	GLCOREAPI void APIENTRY glProgramUniformMatrix4x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
	{
		return context->ProgramUniformMatrix4x2dv(program, location, count, transpose, value);
	}

	GLCOREAPI void APIENTRY glProgramUniformMatrix4x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
	{
		return context->ProgramUniformMatrix4x2fv(program, location, count, transpose, value);
	}

	GLCOREAPI void APIENTRY glProgramUniformMatrix4x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
	{
		return context->ProgramUniformMatrix4x3dv(program, location, count, transpose, value);
	}

	GLCOREAPI void APIENTRY glProgramUniformMatrix4x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
	{
		return context->ProgramUniformMatrix4x3fv(program, location, count, transpose, value);
	}

	GLCOREAPI void APIENTRY glProvokingVertex(GLenum mode)
	{
		return context->ProvokingVertex(mode);
	}

	GLCOREAPI void APIENTRY glPushDebugGroup(GLenum source, GLuint id, GLsizei length, const GLchar* message)
	{
		return context->PushDebugGroup(source, id, length, message);
	}

	GLCOREAPI void APIENTRY glQueryCounter(GLuint id, GLenum target)
	{
		return context->QueryCounter(id, target);
	}

	GLCOREAPI void APIENTRY glReadnPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void* data)
	{
		return context->ReadnPixels(x, y, width, height, format, type, bufSize, data);
	}

	GLCOREAPI void APIENTRY glReleaseShaderCompiler()
	{
		return context->ReleaseShaderCompiler();
	}

	GLCOREAPI void APIENTRY glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
	{
		return context->RenderbufferStorage(target, internalformat, width, height);
	}

	GLCOREAPI void APIENTRY glRenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)
	{
		return context->RenderbufferStorageMultisample(target, samples, internalformat, width, height);
	}

	GLCOREAPI void APIENTRY glResumeTransformFeedback()
	{
		return context->ResumeTransformFeedback();
	}

	GLCOREAPI void APIENTRY glSampleCoverage(GLfloat value, GLboolean invert)
	{
		return context->SampleCoverage(value, invert);
	}

	GLCOREAPI void APIENTRY glSampleMaski(GLuint maskNumber, GLbitfield mask)
	{
		return context->SampleMaski(maskNumber, mask);
	}

	GLCOREAPI void APIENTRY glSamplerParameterIiv(GLuint sampler, GLenum pname, const GLint* param)
	{
		return context->SamplerParameterIiv(sampler, pname, param);
	}

	GLCOREAPI void APIENTRY glSamplerParameterIuiv(GLuint sampler, GLenum pname, const GLuint* param)
	{
		return context->SamplerParameterIuiv(sampler, pname, param);
	}

	GLCOREAPI void APIENTRY glSamplerParameterf(GLuint sampler, GLenum pname, GLfloat param)
	{
		return context->SamplerParameterf(sampler, pname, param);
	}

	GLCOREAPI void APIENTRY glSamplerParameterfv(GLuint sampler, GLenum pname, const GLfloat* param)
	{
		return context->SamplerParameterfv(sampler, pname, param);
	}

	GLCOREAPI void APIENTRY glSamplerParameteri(GLuint sampler, GLenum pname, GLint param)
	{
		return context->SamplerParameteri(sampler, pname, param);
	}

	GLCOREAPI void APIENTRY glSamplerParameteriv(GLuint sampler, GLenum pname, const GLint* param)
	{
		return context->SamplerParameteriv(sampler, pname, param);
	}

	GLCOREAPI void APIENTRY glScissorArrayv(GLuint first, GLsizei count, const GLint* v)
	{
		return context->ScissorArrayv(first, count, v);
	}

	GLCOREAPI void APIENTRY glScissorIndexed(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height)
	{
		return context->ScissorIndexed(index, left, bottom, width, height);
	}

	GLCOREAPI void APIENTRY glScissorIndexedv(GLuint index, const GLint* v)
	{
		return context->ScissorIndexedv(index, v);
	}

	GLCOREAPI void APIENTRY glShaderBinary(GLsizei count, const GLuint* shaders, GLenum binaryformat, const void* binary, GLsizei length)
	{
		return context->ShaderBinary(count, shaders, binaryformat, binary, length);
	}

	GLCOREAPI void APIENTRY glShaderSource(GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length)
	{
		return context->ShaderSource(shader, count, string, length);
	}

	GLCOREAPI void APIENTRY glShaderStorageBlockBinding(GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding)
	{
		return context->ShaderStorageBlockBinding(program, storageBlockIndex, storageBlockBinding);
	}

	GLCOREAPI void APIENTRY glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask)
	{
		return context->StencilFuncSeparate(face, func, ref, mask);
	}

	GLCOREAPI void APIENTRY glStencilMaskSeparate(GLenum face, GLuint mask)
	{
		return context->StencilMaskSeparate(face, mask);
	}

	GLCOREAPI void APIENTRY glStencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass)
	{
		return context->StencilOpSeparate(face, sfail, dpfail, dppass);
	}

	GLCOREAPI void APIENTRY glTexBuffer(GLenum target, GLenum internalformat, GLuint buffer)
	{
		return context->TexBuffer(target, internalformat, buffer);
	}

	GLCOREAPI void APIENTRY glTexBufferRange(GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size)
	{
		return context->TexBufferRange(target, internalformat, buffer, offset, size);
	}

	GLCOREAPI void APIENTRY glTexImage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
	{
		return context->TexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
	}

	GLCOREAPI void APIENTRY glTexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void* pixels)
	{
		return context->TexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels);
	}

	GLCOREAPI void APIENTRY glTexImage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
	{
		return context->TexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
	}

	GLCOREAPI void APIENTRY glTexParameterIiv(GLenum target, GLenum pname, const GLint* params)
	{
		return context->TexParameterIiv(target, pname, params);
	}

	GLCOREAPI void APIENTRY glTexParameterIuiv(GLenum target, GLenum pname, const GLuint* params)
	{
		return context->TexParameterIuiv(target, pname, params);
	}

	GLCOREAPI void APIENTRY glTexStorage1D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width)
	{
		return context->TexStorage1D(target, levels, internalformat, width);
	}

	GLCOREAPI void APIENTRY glTexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
	{
		return context->TexStorage2D(target, levels, internalformat, width, height);
	}

	GLCOREAPI void APIENTRY glTexStorage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
	{
		return context->TexStorage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
	}

	GLCOREAPI void APIENTRY glTexStorage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth)
	{
		return context->TexStorage3D(target, levels, internalformat, width, height, depth);
	}

	GLCOREAPI void APIENTRY glTexStorage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
	{
		return context->TexStorage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
	}

	GLCOREAPI void APIENTRY glTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels)
	{
		return context->TexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
	}

	GLCOREAPI void APIENTRY glTextureBarrier()
	{
		return context->TextureBarrier();
	}

	GLCOREAPI void APIENTRY glTextureBuffer(GLuint texture, GLenum internalformat, GLuint buffer)
	{
		return context->TextureBuffer(texture, internalformat, buffer);
	}

	GLCOREAPI void APIENTRY glTextureBufferRange(GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size)
	{
		return context->TextureBufferRange(texture, internalformat, buffer, offset, size);
	}

	GLCOREAPI void APIENTRY glTextureParameterIiv(GLuint texture, GLenum pname, const GLint* params)
	{
		return context->TextureParameterIiv(texture, pname, params);
	}

	GLCOREAPI void APIENTRY glTextureParameterIuiv(GLuint texture, GLenum pname, const GLuint* params)
	{
		return context->TextureParameterIuiv(texture, pname, params);
	}

	GLCOREAPI void APIENTRY glTextureParameterf(GLuint texture, GLenum pname, GLfloat param)
	{
		return context->TextureParameterf(texture, pname, param);
	}

	GLCOREAPI void APIENTRY glTextureParameterfv(GLuint texture, GLenum pname, const GLfloat* param)
	{
		return context->TextureParameterfv(texture, pname, param);
	}

	GLCOREAPI void APIENTRY glTextureParameteri(GLuint texture, GLenum pname, GLint param)
	{
		return context->TextureParameteri(texture, pname, param);
	}

	GLCOREAPI void APIENTRY glTextureParameteriv(GLuint texture, GLenum pname, const GLint* param)
	{
		return context->TextureParameteriv(texture, pname, param);
	}

	GLCOREAPI void APIENTRY glTextureStorage1D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width)
	{
		return context->TextureStorage1D(texture, levels, internalformat, width);
	}

	GLCOREAPI void APIENTRY glTextureStorage2D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
	{
		return context->TextureStorage2D(texture, levels, internalformat, width, height);
	}

	GLCOREAPI void APIENTRY glTextureStorage2DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
	{
		return context->TextureStorage2DMultisample(texture, samples, internalformat, width, height, fixedsamplelocations);
	}

	GLCOREAPI void APIENTRY glTextureStorage3D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth)
	{
		return context->TextureStorage3D(texture, levels, internalformat, width, height, depth);
	}

	GLCOREAPI void APIENTRY glTextureStorage3DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
	{
		return context->TextureStorage3DMultisample(texture, samples, internalformat, width, height, depth, fixedsamplelocations);
	}

	GLCOREAPI void APIENTRY glTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels)
	{
		return context->TextureSubImage1D(texture, level, xoffset, width, format, type, pixels);
	}

	GLCOREAPI void APIENTRY glTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels)
	{
		return context->TextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, type, pixels);
	}

	GLCOREAPI void APIENTRY glTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels)
	{
		return context->TextureSubImage3D(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
	}

	GLCOREAPI void APIENTRY glTextureView(GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers)
	{
		return context->TextureView(texture, target, origtexture, internalformat, minlevel, numlevels, minlayer, numlayers);
	}

	GLCOREAPI void APIENTRY glTransformFeedbackBufferBase(GLuint xfb, GLuint index, GLuint buffer)
	{
		return context->TransformFeedbackBufferBase(xfb, index, buffer);
	}

	GLCOREAPI void APIENTRY glTransformFeedbackBufferRange(GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size)
	{
		return context->TransformFeedbackBufferRange(xfb, index, buffer, offset, size);
	}

	GLCOREAPI void APIENTRY glTransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar* const* varyings, GLenum bufferMode)
	{
		return context->TransformFeedbackVaryings(program, count, varyings, bufferMode);
	}

	GLCOREAPI void APIENTRY glUniform1d(GLint location, GLdouble x)
	{
		return context->Uniform1d(location, x);
	}

	GLCOREAPI void APIENTRY glUniform1dv(GLint location, GLsizei count, const GLdouble* value)
	{
		return context->Uniform1dv(location, count, value);
	}

	GLCOREAPI void APIENTRY glUniform1f(GLint location, GLfloat v0)
	{
		return context->Uniform1f(location, v0);
	}

	GLCOREAPI void APIENTRY glUniform1fv(GLint location, GLsizei count, const GLfloat* value)
	{
		return context->Uniform1fv(location, count, value);
	}

	GLCOREAPI void APIENTRY glUniform1i(GLint location, GLint v0)
	{
		return context->Uniform1i(location, v0);
	}

	GLCOREAPI void APIENTRY glUniform1iv(GLint location, GLsizei count, const GLint* value)
	{
		return context->Uniform1iv(location, count, value);
	}

	GLCOREAPI void APIENTRY glUniform1ui(GLint location, GLuint v0)
	{
		return context->Uniform1ui(location, v0);
	}

	GLCOREAPI void APIENTRY glUniform1uiv(GLint location, GLsizei count, const GLuint* value)
	{
		return context->Uniform1uiv(location, count, value);
	}

	GLCOREAPI void APIENTRY glUniform2d(GLint location, GLdouble x, GLdouble y)
	{
		return context->Uniform2d(location, x, y);
	}

	GLCOREAPI void APIENTRY glUniform2dv(GLint location, GLsizei count, const GLdouble* value)
	{
		return context->Uniform2dv(location, count, value);
	}

	GLCOREAPI void APIENTRY glUniform2f(GLint location, GLfloat v0, GLfloat v1)
	{
		return context->Uniform2f(location, v0, v1);
	}

	GLCOREAPI void APIENTRY glUniform2fv(GLint location, GLsizei count, const GLfloat* value)
	{
		return context->Uniform2fv(location, count, value);
	}

	GLCOREAPI void APIENTRY glUniform2i(GLint location, GLint v0, GLint v1)
	{
		return context->Uniform2i(location, v0, v1);
	}

	GLCOREAPI void APIENTRY glUniform2iv(GLint location, GLsizei count, const GLint* value)
	{
		return context->Uniform2iv(location, count, value);
	}

	GLCOREAPI void APIENTRY glUniform2ui(GLint location, GLuint v0, GLuint v1)
	{
		return context->Uniform2ui(location, v0, v1);
	}

	GLCOREAPI void APIENTRY glUniform2uiv(GLint location, GLsizei count, const GLuint* value)
	{
		return context->Uniform2uiv(location, count, value);
	}

	GLCOREAPI void APIENTRY glUniform3d(GLint location, GLdouble x, GLdouble y, GLdouble z)
	{
		return context->Uniform3d(location, x, y, z);
	}

	GLCOREAPI void APIENTRY glUniform3dv(GLint location, GLsizei count, const GLdouble* value)
	{
		return context->Uniform3dv(location, count, value);
	}

	GLCOREAPI void APIENTRY glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
	{
		return context->Uniform3f(location, v0, v1, v2);
	}

	GLCOREAPI void APIENTRY glUniform3fv(GLint location, GLsizei count, const GLfloat* value)
	{
		return context->Uniform3fv(location, count, value);
	}

	GLCOREAPI void APIENTRY glUniform3i(GLint location, GLint v0, GLint v1, GLint v2)
	{
		return context->Uniform3i(location, v0, v1, v2);
	}

	GLCOREAPI void APIENTRY glUniform3iv(GLint location, GLsizei count, const GLint* value)
	{
		return context->Uniform3iv(location, count, value);
	}

	GLCOREAPI void APIENTRY glUniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2)
	{
		return context->Uniform3ui(location, v0, v1, v2);
	}

	GLCOREAPI void APIENTRY glUniform3uiv(GLint location, GLsizei count, const GLuint* value)
	{
		return context->Uniform3uiv(location, count, value);
	}

	GLCOREAPI void APIENTRY glUniform4d(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
	{
		return context->Uniform4d(location, x, y, z, w);
	}

	GLCOREAPI void APIENTRY glUniform4dv(GLint location, GLsizei count, const GLdouble* value)
	{
		return context->Uniform4dv(location, count, value);
	}

	GLCOREAPI void APIENTRY glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
	{
		return context->Uniform4f(location, v0, v1, v2, v3);
	}

	GLCOREAPI void APIENTRY glUniform4fv(GLint location, GLsizei count, const GLfloat* value)
	{
		return context->Uniform4fv(location, count, value);
	}

	GLCOREAPI void APIENTRY glUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
	{
		return context->Uniform4i(location, v0, v1, v2, v3);
	}

	GLCOREAPI void APIENTRY glUniform4iv(GLint location, GLsizei count, const GLint* value)
	{
		return context->Uniform4iv(location, count, value);
	}

	GLCOREAPI void APIENTRY glUniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
	{
		return context->Uniform4ui(location, v0, v1, v2, v3);
	}

	GLCOREAPI void APIENTRY glUniform4uiv(GLint location, GLsizei count, const GLuint* value)
	{
		return context->Uniform4uiv(location, count, value);
	}

	GLCOREAPI void APIENTRY glUniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding)
	{
		return context->UniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);
	}

	GLCOREAPI void APIENTRY glUniformMatrix2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
	{
		return context->UniformMatrix2dv(location, count, transpose, value);
	}

	GLCOREAPI void APIENTRY glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
	{
		return context->UniformMatrix2fv(location, count, transpose, value);
	}

	GLCOREAPI void APIENTRY glUniformMatrix2x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
	{
		return context->UniformMatrix2x3dv(location, count, transpose, value);
	}

	GLCOREAPI void APIENTRY glUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
	{
		return context->UniformMatrix2x3fv(location, count, transpose, value);
	}

	GLCOREAPI void APIENTRY glUniformMatrix2x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
	{
		return context->UniformMatrix2x4dv(location, count, transpose, value);
	}

	GLCOREAPI void APIENTRY glUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
	{
		return context->UniformMatrix2x4fv(location, count, transpose, value);
	}

	GLCOREAPI void APIENTRY glUniformMatrix3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
	{
		return context->UniformMatrix3dv(location, count, transpose, value);
	}

	GLCOREAPI void APIENTRY glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
	{
		return context->UniformMatrix3fv(location, count, transpose, value);
	}

	GLCOREAPI void APIENTRY glUniformMatrix3x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
	{
		return context->UniformMatrix3x2dv(location, count, transpose, value);
	}

	GLCOREAPI void APIENTRY glUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
	{
		return context->UniformMatrix3x2fv(location, count, transpose, value);
	}

	GLCOREAPI void APIENTRY glUniformMatrix3x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
	{
		return context->UniformMatrix3x4dv(location, count, transpose, value);
	}

	GLCOREAPI void APIENTRY glUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
	{
		return context->UniformMatrix3x4fv(location, count, transpose, value);
	}

	GLCOREAPI void APIENTRY glUniformMatrix4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
	{
		return context->UniformMatrix4dv(location, count, transpose, value);
	}

	GLCOREAPI void APIENTRY glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
	{
		return context->UniformMatrix4fv(location, count, transpose, value);
	}

	GLCOREAPI void APIENTRY glUniformMatrix4x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
	{
		return context->UniformMatrix4x2dv(location, count, transpose, value);
	}

	GLCOREAPI void APIENTRY glUniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
	{
		return context->UniformMatrix4x2fv(location, count, transpose, value);
	}

	GLCOREAPI void APIENTRY glUniformMatrix4x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
	{
		return context->UniformMatrix4x3dv(location, count, transpose, value);
	}

	GLCOREAPI void APIENTRY glUniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
	{
		return context->UniformMatrix4x3fv(location, count, transpose, value);
	}

	GLCOREAPI void APIENTRY glUniformSubroutinesuiv(GLenum shadertype, GLsizei count, const GLuint* indices)
	{
		return context->UniformSubroutinesuiv(shadertype, count, indices);
	}

	GLCOREAPI GLboolean APIENTRY glUnmapBuffer(GLenum target)
	{
		return context->UnmapBuffer(target);
	}

	GLCOREAPI GLboolean APIENTRY glUnmapNamedBuffer(GLuint buffer)
	{
		return context->UnmapNamedBuffer(buffer);
	}

	GLCOREAPI void APIENTRY glUseProgram(GLuint program)
	{
		return context->UseProgram(program);
	}

	GLCOREAPI void APIENTRY glUseProgramStages(GLuint pipeline, GLbitfield stages, GLuint program)
	{
		return context->UseProgramStages(pipeline, stages, program);
	}

	GLCOREAPI void APIENTRY glValidateProgram(GLuint program)
	{
		return context->ValidateProgram(program);
	}

	GLCOREAPI void APIENTRY glValidateProgramPipeline(GLuint pipeline)
	{
		return context->ValidateProgramPipeline(pipeline);
	}

	GLCOREAPI void APIENTRY glVertexArrayAttribBinding(GLuint vaobj, GLuint attribindex, GLuint bindingindex)
	{
		return context->VertexArrayAttribBinding(vaobj, attribindex, bindingindex);
	}

	GLCOREAPI void APIENTRY glVertexArrayAttribFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset)
	{
		return context->VertexArrayAttribFormat(vaobj, attribindex, size, type, normalized, relativeoffset);
	}

	GLCOREAPI void APIENTRY glVertexArrayAttribIFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
	{
		return context->VertexArrayAttribIFormat(vaobj, attribindex, size, type, relativeoffset);
	}

	GLCOREAPI void APIENTRY glVertexArrayAttribLFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
	{
		return context->VertexArrayAttribLFormat(vaobj, attribindex, size, type, relativeoffset);
	}

	GLCOREAPI void APIENTRY glVertexArrayBindingDivisor(GLuint vaobj, GLuint bindingindex, GLuint divisor)
	{
		return context->VertexArrayBindingDivisor(vaobj, bindingindex, divisor);
	}

	GLCOREAPI void APIENTRY glVertexArrayElementBuffer(GLuint vaobj, GLuint buffer)
	{
		return context->VertexArrayElementBuffer(vaobj, buffer);
	}

	GLCOREAPI void APIENTRY glVertexArrayVertexBuffer(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride)
	{
		return context->VertexArrayVertexBuffer(vaobj, bindingindex, buffer, offset, stride);
	}

	GLCOREAPI void APIENTRY glVertexArrayVertexBuffers(GLuint vaobj, GLuint first, GLsizei count, const GLuint* buffers, const GLintptr* offsets, const GLsizei* strides)
	{
		return context->VertexArrayVertexBuffers(vaobj, first, count, buffers, offsets, strides);
	}

	GLCOREAPI void APIENTRY glVertexAttrib1d(GLuint index, GLdouble x)
	{
		return context->VertexAttrib1d(index, x);
	}

	GLCOREAPI void APIENTRY glVertexAttrib1dv(GLuint index, const GLdouble* v)
	{
		return context->VertexAttrib1dv(index, v);
	}

	GLCOREAPI void APIENTRY glVertexAttrib1f(GLuint index, GLfloat x)
	{
		return context->VertexAttrib1f(index, x);
	}

	GLCOREAPI void APIENTRY glVertexAttrib1fv(GLuint index, const GLfloat* v)
	{
		return context->VertexAttrib1fv(index, v);
	}

	GLCOREAPI void APIENTRY glVertexAttrib1s(GLuint index, GLshort x)
	{
		return context->VertexAttrib1s(index, x);
	}

	GLCOREAPI void APIENTRY glVertexAttrib1sv(GLuint index, const GLshort* v)
	{
		return context->VertexAttrib1sv(index, v);
	}

	GLCOREAPI void APIENTRY glVertexAttrib2d(GLuint index, GLdouble x, GLdouble y)
	{
		return context->VertexAttrib2d(index, x, y);
	}

	GLCOREAPI void APIENTRY glVertexAttrib2dv(GLuint index, const GLdouble* v)
	{
		return context->VertexAttrib2dv(index, v);
	}

	GLCOREAPI void APIENTRY glVertexAttrib2f(GLuint index, GLfloat x, GLfloat y)
	{
		return context->VertexAttrib2f(index, x, y);
	}

	GLCOREAPI void APIENTRY glVertexAttrib2fv(GLuint index, const GLfloat* v)
	{
		return context->VertexAttrib2fv(index, v);
	}

	GLCOREAPI void APIENTRY glVertexAttrib2s(GLuint index, GLshort x, GLshort y)
	{
		return context->VertexAttrib2s(index, x, y);
	}

	GLCOREAPI void APIENTRY glVertexAttrib2sv(GLuint index, const GLshort* v)
	{
		return context->VertexAttrib2sv(index, v);
	}

	GLCOREAPI void APIENTRY glVertexAttrib3d(GLuint index, GLdouble x, GLdouble y, GLdouble z)
	{
		return context->VertexAttrib3d(index, x, y, z);
	}

	GLCOREAPI void APIENTRY glVertexAttrib3dv(GLuint index, const GLdouble* v)
	{
		return context->VertexAttrib3dv(index, v);
	}

	GLCOREAPI void APIENTRY glVertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z)
	{
		return context->VertexAttrib3f(index, x, y, z);
	}

	GLCOREAPI void APIENTRY glVertexAttrib3fv(GLuint index, const GLfloat* v)
	{
		return context->VertexAttrib3fv(index, v);
	}

	GLCOREAPI void APIENTRY glVertexAttrib3s(GLuint index, GLshort x, GLshort y, GLshort z)
	{
		return context->VertexAttrib3s(index, x, y, z);
	}

	GLCOREAPI void APIENTRY glVertexAttrib3sv(GLuint index, const GLshort* v)
	{
		return context->VertexAttrib3sv(index, v);
	}

	GLCOREAPI void APIENTRY glVertexAttrib4Nbv(GLuint index, const GLbyte* v)
	{
		return context->VertexAttrib4Nbv(index, v);
	}

	GLCOREAPI void APIENTRY glVertexAttrib4Niv(GLuint index, const GLint* v)
	{
		return context->VertexAttrib4Niv(index, v);
	}

	GLCOREAPI void APIENTRY glVertexAttrib4Nsv(GLuint index, const GLshort* v)
	{
		return context->VertexAttrib4Nsv(index, v);
	}

	GLCOREAPI void APIENTRY glVertexAttrib4Nub(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w)
	{
		return context->VertexAttrib4Nub(index, x, y, z, w);
	}

	GLCOREAPI void APIENTRY glVertexAttrib4Nubv(GLuint index, const GLubyte* v)
	{
		return context->VertexAttrib4Nubv(index, v);
	}

	GLCOREAPI void APIENTRY glVertexAttrib4Nuiv(GLuint index, const GLuint* v)
	{
		return context->VertexAttrib4Nuiv(index, v);
	}

	GLCOREAPI void APIENTRY glVertexAttrib4Nusv(GLuint index, const GLushort* v)
	{
		return context->VertexAttrib4Nusv(index, v);
	}

	GLCOREAPI void APIENTRY glVertexAttrib4bv(GLuint index, const GLbyte* v)
	{
		return context->VertexAttrib4bv(index, v);
	}

	GLCOREAPI void APIENTRY glVertexAttrib4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
	{
		return context->VertexAttrib4d(index, x, y, z, w);
	}

	GLCOREAPI void APIENTRY glVertexAttrib4dv(GLuint index, const GLdouble* v)
	{
		return context->VertexAttrib4dv(index, v);
	}

	GLCOREAPI void APIENTRY glVertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
	{
		return context->VertexAttrib4f(index, x, y, z, w);
	}

	GLCOREAPI void APIENTRY glVertexAttrib4fv(GLuint index, const GLfloat* v)
	{
		return context->VertexAttrib4fv(index, v);
	}

	GLCOREAPI void APIENTRY glVertexAttrib4iv(GLuint index, const GLint* v)
	{
		return context->VertexAttrib4iv(index, v);
	}

	GLCOREAPI void APIENTRY glVertexAttrib4s(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w)
	{
		return context->VertexAttrib4s(index, x, y, z, w);
	}

	GLCOREAPI void APIENTRY glVertexAttrib4sv(GLuint index, const GLshort* v)
	{
		return context->VertexAttrib4sv(index, v);
	}

	GLCOREAPI void APIENTRY glVertexAttrib4ubv(GLuint index, const GLubyte* v)
	{
		return context->VertexAttrib4ubv(index, v);
	}

	GLCOREAPI void APIENTRY glVertexAttrib4uiv(GLuint index, const GLuint* v)
	{
		return context->VertexAttrib4uiv(index, v);
	}

	GLCOREAPI void APIENTRY glVertexAttrib4usv(GLuint index, const GLushort* v)
	{
		return context->VertexAttrib4usv(index, v);
	}

	GLCOREAPI void APIENTRY glVertexAttribBinding(GLuint attribindex, GLuint bindingindex)
	{
		return context->VertexAttribBinding(attribindex, bindingindex);
	}

	GLCOREAPI void APIENTRY glVertexAttribDivisor(GLuint index, GLuint divisor)
	{
		return context->VertexAttribDivisor(index, divisor);
	}

	GLCOREAPI void APIENTRY glVertexAttribFormat(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset)
	{
		return context->VertexAttribFormat(attribindex, size, type, normalized, relativeoffset);
	}

	GLCOREAPI void APIENTRY glVertexAttribI1i(GLuint index, GLint x)
	{
		return context->VertexAttribI1i(index, x);
	}

	GLCOREAPI void APIENTRY glVertexAttribI1iv(GLuint index, const GLint* v)
	{
		return context->VertexAttribI1iv(index, v);
	}

	GLCOREAPI void APIENTRY glVertexAttribI1ui(GLuint index, GLuint x)
	{
		return context->VertexAttribI1ui(index, x);
	}

	GLCOREAPI void APIENTRY glVertexAttribI1uiv(GLuint index, const GLuint* v)
	{
		return context->VertexAttribI1uiv(index, v);
	}

	GLCOREAPI void APIENTRY glVertexAttribI2i(GLuint index, GLint x, GLint y)
	{
		return context->VertexAttribI2i(index, x, y);
	}

	GLCOREAPI void APIENTRY glVertexAttribI2iv(GLuint index, const GLint* v)
	{
		return context->VertexAttribI2iv(index, v);
	}

	GLCOREAPI void APIENTRY glVertexAttribI2ui(GLuint index, GLuint x, GLuint y)
	{
		return context->VertexAttribI2ui(index, x, y);
	}

	GLCOREAPI void APIENTRY glVertexAttribI2uiv(GLuint index, const GLuint* v)
	{
		return context->VertexAttribI2uiv(index, v);
	}

	GLCOREAPI void APIENTRY glVertexAttribI3i(GLuint index, GLint x, GLint y, GLint z)
	{
		return context->VertexAttribI3i(index, x, y, z);
	}

	GLCOREAPI void APIENTRY glVertexAttribI3iv(GLuint index, const GLint* v)
	{
		return context->VertexAttribI3iv(index, v);
	}

	GLCOREAPI void APIENTRY glVertexAttribI3ui(GLuint index, GLuint x, GLuint y, GLuint z)
	{
		return context->VertexAttribI3ui(index, x, y, z);
	}

	GLCOREAPI void APIENTRY glVertexAttribI3uiv(GLuint index, const GLuint* v)
	{
		return context->VertexAttribI3uiv(index, v);
	}

	GLCOREAPI void APIENTRY glVertexAttribI4bv(GLuint index, const GLbyte* v)
	{
		return context->VertexAttribI4bv(index, v);
	}

	GLCOREAPI void APIENTRY glVertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w)
	{
		return context->VertexAttribI4i(index, x, y, z, w);
	}

	GLCOREAPI void APIENTRY glVertexAttribI4iv(GLuint index, const GLint* v)
	{
		return context->VertexAttribI4iv(index, v);
	}

	GLCOREAPI void APIENTRY glVertexAttribI4sv(GLuint index, const GLshort* v)
	{
		return context->VertexAttribI4sv(index, v);
	}

	GLCOREAPI void APIENTRY glVertexAttribI4ubv(GLuint index, const GLubyte* v)
	{
		return context->VertexAttribI4ubv(index, v);
	}

	GLCOREAPI void APIENTRY glVertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w)
	{
		return context->VertexAttribI4ui(index, x, y, z, w);
	}

	GLCOREAPI void APIENTRY glVertexAttribI4uiv(GLuint index, const GLuint* v)
	{
		return context->VertexAttribI4uiv(index, v);
	}

	GLCOREAPI void APIENTRY glVertexAttribI4usv(GLuint index, const GLushort* v)
	{
		return context->VertexAttribI4usv(index, v);
	}

	GLCOREAPI void APIENTRY glVertexAttribIFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
	{
		return context->VertexAttribIFormat(attribindex, size, type, relativeoffset);
	}

	GLCOREAPI void APIENTRY glVertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer)
	{
		return context->VertexAttribIPointer(index, size, type, stride, pointer);
	}

	GLCOREAPI void APIENTRY glVertexAttribL1d(GLuint index, GLdouble x)
	{
		return context->VertexAttribL1d(index, x);
	}

	GLCOREAPI void APIENTRY glVertexAttribL1dv(GLuint index, const GLdouble* v)
	{
		return context->VertexAttribL1dv(index, v);
	}

	GLCOREAPI void APIENTRY glVertexAttribL2d(GLuint index, GLdouble x, GLdouble y)
	{
		return context->VertexAttribL2d(index, x, y);
	}

	GLCOREAPI void APIENTRY glVertexAttribL2dv(GLuint index, const GLdouble* v)
	{
		return context->VertexAttribL2dv(index, v);
	}

	GLCOREAPI void APIENTRY glVertexAttribL3d(GLuint index, GLdouble x, GLdouble y, GLdouble z)
	{
		return context->VertexAttribL3d(index, x, y, z);
	}

	GLCOREAPI void APIENTRY glVertexAttribL3dv(GLuint index, const GLdouble* v)
	{
		return context->VertexAttribL3dv(index, v);
	}

	GLCOREAPI void APIENTRY glVertexAttribL4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
	{
		return context->VertexAttribL4d(index, x, y, z, w);
	}

	GLCOREAPI void APIENTRY glVertexAttribL4dv(GLuint index, const GLdouble* v)
	{
		return context->VertexAttribL4dv(index, v);
	}

	GLCOREAPI void APIENTRY glVertexAttribLFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
	{
		return context->VertexAttribLFormat(attribindex, size, type, relativeoffset);
	}

	GLCOREAPI void APIENTRY glVertexAttribLPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer)
	{
		return context->VertexAttribLPointer(index, size, type, stride, pointer);
	}

	GLCOREAPI void APIENTRY glVertexAttribP1ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
	{
		return context->VertexAttribP1ui(index, type, normalized, value);
	}

	GLCOREAPI void APIENTRY glVertexAttribP1uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint* value)
	{
		return context->VertexAttribP1uiv(index, type, normalized, value);
	}

	GLCOREAPI void APIENTRY glVertexAttribP2ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
	{
		return context->VertexAttribP2ui(index, type, normalized, value);
	}

	GLCOREAPI void APIENTRY glVertexAttribP2uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint* value)
	{
		return context->VertexAttribP2uiv(index, type, normalized, value);
	}

	GLCOREAPI void APIENTRY glVertexAttribP3ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
	{
		return context->VertexAttribP3ui(index, type, normalized, value);
	}

	GLCOREAPI void APIENTRY glVertexAttribP3uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint* value)
	{
		return context->VertexAttribP3uiv(index, type, normalized, value);
	}

	GLCOREAPI void APIENTRY glVertexAttribP4ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
	{
		return context->VertexAttribP4ui(index, type, normalized, value);
	}

	GLCOREAPI void APIENTRY glVertexAttribP4uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint* value)
	{
		return context->VertexAttribP4uiv(index, type, normalized, value);
	}

	GLCOREAPI void APIENTRY glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
	{
		return context->VertexAttribPointer(index, size, type, normalized, stride, pointer);
	}

	GLCOREAPI void APIENTRY glVertexBindingDivisor(GLuint bindingindex, GLuint divisor)
	{
		return context->VertexBindingDivisor(bindingindex, divisor);
	}

	GLCOREAPI void APIENTRY glViewportArrayv(GLuint first, GLsizei count, const GLfloat* v)
	{
		return context->ViewportArrayv(first, count, v);
	}

	GLCOREAPI void APIENTRY glViewportIndexedf(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h)
	{
		return context->ViewportIndexedf(index, x, y, w, h);
	}

	GLCOREAPI void APIENTRY glViewportIndexedfv(GLuint index, const GLfloat* v)
	{
		return context->ViewportIndexedfv(index, v);
	}

	GLCOREAPI void APIENTRY glWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout)
	{
		return context->WaitSync(sync, flags, timeout);
	}

	GLCOREAPI BOOL APIENTRY wglSwapIntervalEXT(int interval)
	{
		return context->wglSwapInterval(interval);
	}
}
