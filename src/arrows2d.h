#pragma once


#include <synapse/Renderer>
#include <glm/glm.hpp>

using namespace Syn;


//
class Arrows2D
{
public:
    Arrows2D(const Ref<FramebufferBase> &_vector_field, 
             uint32_t _sampling_rate=1,
             const glm::vec2 &_vp=Renderer::getViewportF());
    ~Arrows2D() = default;

    void render();
    void update();


private:
    glm::ivec2 m_dim = { 0, 0 };
    glm::vec2 m_texelSize;              // texel size in of UV-space [0..1]
    Ref<FramebufferBase> m_vectorField; // pointer to the field, for shader texture retrival

    glm::vec2 m_vp;                 // viewport size of the frambuffer, used for calculating arrow size
    float m_arrowSize;              // size of the arrow, calculated based on the dim and the vp, and used as a uniform in the shader

    uint32_t m_samplingRate;        // min 0, downsampling of the dim

    //
    uint32_t m_arrowCount = 0;      // calculated from dim and sampling rate
    Ref<VertexArray> m_vao;
    Ref<Shader> m_shader;

};


