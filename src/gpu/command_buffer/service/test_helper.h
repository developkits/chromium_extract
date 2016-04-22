// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GPU_COMMAND_BUFFER_SERVICE_TEST_HELPER_H_
#define GPU_COMMAND_BUFFER_SERVICE_TEST_HELPER_H_

#include <stddef.h>

#include <string>
#include <vector>

#include "gpu/command_buffer/service/shader_translator.h"
#include "ui/gl/gl_implementation.h"
#include "ui/gl/gl_mock.h"

namespace gpu {
namespace gles2 {

struct DisallowedFeatures;
class Buffer;
class BufferManager;
class FeatureInfo;
class MockErrorState;
class Shader;
class TextureRef;
class TextureManager;

class TestHelper {
 public:
  static const GLuint kServiceBlackTexture2dId = 701;
  static const GLuint kServiceDefaultTexture2dId = 702;
  static const GLuint kServiceBlackTexture3dId = 703;
  static const GLuint kServiceDefaultTexture3dId = 704;
  static const GLuint kServiceBlackTexture2dArrayId = 705;
  static const GLuint kServiceDefaultTexture2dArrayId = 706;
  static const GLuint kServiceBlackTextureCubemapId = 707;
  static const GLuint kServiceDefaultTextureCubemapId = 708;
  static const GLuint kServiceBlackExternalTextureId = 709;
  static const GLuint kServiceDefaultExternalTextureId = 710;
  static const GLuint kServiceBlackRectangleTextureId = 711;
  static const GLuint kServiceDefaultRectangleTextureId = 712;

  static const GLint kMaxSamples = 4;
  static const GLint kMaxRenderbufferSize = 1024;
  static const GLint kMaxTextureSize = 2048;
  static const GLint kMaxCubeMapTextureSize = 256;
  static const GLint kMax3DTextureSize = 256;
  static const GLint kMaxRectangleTextureSize = 64;
  static const GLint kNumVertexAttribs = 16;
  static const GLint kNumTextureUnits = 8;
  static const GLint kMaxTextureImageUnits = 8;
  static const GLint kMaxVertexTextureImageUnits = 2;
  static const GLint kMaxFragmentUniformVectors = 16;
  static const GLint kMaxFragmentUniformComponents =
      kMaxFragmentUniformVectors * 4;
  static const GLint kMaxVaryingVectors = 8;
  static const GLint kMaxVaryingFloats = kMaxVaryingVectors * 4;
  static const GLint kMaxVertexUniformVectors = 128;
  static const GLint kMaxVertexUniformComponents = kMaxVertexUniformVectors * 4;

  struct AttribInfo {
    const char* name;
    GLint size;
    GLenum type;
    GLint location;
  };

  struct UniformInfo {
    const char* name;
    GLint size;
    GLenum type;
    GLint fake_location;
    GLint real_location;
    GLint desired_location;
    const char* good_name;
  };

  struct VaryingInfo {
    const char* name;
    GLint size;
    GLenum type;
    GLint fake_location;
    GLint real_location;
    GLint desired_location;
  };
  struct ProgramOutputInfo {
    const char* name;
    GLint size;
    GLenum type;
    GLint color_name;
    GLuint index;
  };

  static void SetupContextGroupInitExpectations(
      ::gfx::MockGLInterface* gl,
      const DisallowedFeatures& disallowed_features,
      const char* extensions,
      const char* gl_version,
      bool bind_generates_resource);
  static void SetupFeatureInfoInitExpectations(
      ::gfx::MockGLInterface* gl, const char* extensions);
  static void SetupFeatureInfoInitExpectationsWithGLVersion(
      ::gfx::MockGLInterface* gl,
      const char* extensions,
      const char* gl_renderer,
      const char* gl_version);
  static void SetupTextureManagerInitExpectations(::gfx::MockGLInterface* gl,
                                                  bool is_es3_enabled,
                                                  const char* extensions,
                                                  bool use_default_textures);
  static void SetupTextureManagerDestructionExpectations(
      ::gfx::MockGLInterface* gl,
      bool is_es3_enabled,
      const char* extensions,
      bool use_default_textures);

  static void SetupExpectationsForClearingUniforms(
      ::gfx::MockGLInterface* gl, UniformInfo* uniforms, size_t num_uniforms);

  static void SetupShaderExpectations(::gfx::MockGLInterface* gl,
                                      const FeatureInfo* feature_info,
                                      AttribInfo* attribs,
                                      size_t num_attribs,
                                      UniformInfo* uniforms,
                                      size_t num_uniforms,
                                      GLuint service_id);

  static void SetupShaderExpectationsWithVaryings(
      ::gfx::MockGLInterface* gl,
      const FeatureInfo* feature_info,
      AttribInfo* attribs,
      size_t num_attribs,
      UniformInfo* uniforms,
      size_t num_uniforms,
      VaryingInfo* varyings,
      size_t num_varyings,
      ProgramOutputInfo* program_outputs,
      size_t num_program_outputs,
      GLuint service_id);

  static void SetupProgramSuccessExpectations(
      ::gfx::MockGLInterface* gl,
      const FeatureInfo* feature_info,
      AttribInfo* attribs,
      size_t num_attribs,
      UniformInfo* uniforms,
      size_t num_uniforms,
      VaryingInfo* varyings,
      size_t num_varyings,
      ProgramOutputInfo* program_outputs,
      size_t num_program_outputs,
      GLuint service_id);

  static void DoBufferData(
      ::gfx::MockGLInterface* gl, MockErrorState* error_state,
      BufferManager* manager, Buffer* buffer, GLenum target, GLsizeiptr size,
      GLenum usage, const GLvoid* data, GLenum error);

  static void SetTexParameteriWithExpectations(
      ::gfx::MockGLInterface* gl, MockErrorState* error_state,
      TextureManager* manager, TextureRef* texture_ref,
      GLenum pname, GLint value, GLenum error);

  static void SetShaderStates(
      ::gfx::MockGLInterface* gl,
      Shader* shader,
      bool expected_valid,
      const std::string* const expected_log_info,
      const std::string* const expected_translated_source,
      const int* const expected_shader_version,
      const AttributeMap* const expected_attrib_map,
      const UniformMap* const expected_uniform_map,
      const VaryingMap* const expected_varying_map,
      const InterfaceBlockMap* const expected_interface_block_map,
      const OutputVariableList* const expected_output_variable_list,
      const NameMap* const expected_name_map);

  static void SetShaderStates(
      ::gfx::MockGLInterface* gl, Shader* shader, bool valid);

  static sh::Attribute ConstructAttribute(
      GLenum type, GLint array_size, GLenum precision,
      bool static_use, const std::string& name);
  static sh::Uniform ConstructUniform(
      GLenum type, GLint array_size, GLenum precision,
      bool static_use, const std::string& name);
  static sh::Varying ConstructVarying(
      GLenum type, GLint array_size, GLenum precision,
      bool static_use, const std::string& name);
  static sh::OutputVariable ConstructOutputVariable(GLenum type,
                                                    GLint array_size,
                                                    GLenum precision,
                                                    bool static_use,
                                                    const std::string& name);

 private:
  static void SetupTextureInitializationExpectations(::gfx::MockGLInterface* gl,
                                                     GLenum target,
                                                     bool use_default_textures);
  static void SetupTextureDestructionExpectations(::gfx::MockGLInterface* gl,
                                                  GLenum target,
                                                  bool use_default_textures);

  static std::vector<std::string> split_extensions_;
};

// This object temporaritly Sets what gfx::GetGLImplementation returns. During
// testing the GLImplementation is set to kGLImplemenationMockGL but lots of
// code branches based on what gfx::GetGLImplementation returns.
class ScopedGLImplementationSetter {
 public:
  explicit ScopedGLImplementationSetter(gfx::GLImplementation implementation);
  ~ScopedGLImplementationSetter();

 private:
  gfx::GLImplementation old_implementation_;
};

}  // namespace gles2
}  // namespace gpu

#endif  // GPU_COMMAND_BUFFER_SERVICE_TEST_HELPER_H_

