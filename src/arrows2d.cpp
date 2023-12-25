
#include "arrows2d.h"

#include <synapse/API>
#include <synapse/Debug>


//
Arrows2D::Arrows2D(const Ref<FramebufferBase> &_vector_field, 
                   uint32_t _sampling_rate, 
                   const glm::vec2 &_vp)
{

    m_dim = _vector_field->getSize();
    m_texelSize = 1.0f / glm::vec2(m_dim[0], m_dim[1]);
    m_vectorField = _vector_field;
    
    m_vp = _vp;

    m_samplingRate = (_sampling_rate >= 1 ? _sampling_rate : 1);

    update();

}

//---------------------------------------------------------------------------------------
void Arrows2D::render()
{
    static auto &renderer = Renderer::get();
    
    m_shader->enable();
    m_vectorField->bindTexture(0);
    m_shader->setUniform1i("u_vector_field", 0);
    m_shader->setUniform1f("u_arrow_size", m_arrowSize);

    renderer.drawArrays(m_vao, m_arrowCount, 0, false, GL_POINTS);
    
}

//---------------------------------------------------------------------------------------
void Arrows2D::update()
{
    Timer t(__func__, true);   
    int new_x = m_dim.x / m_samplingRate;
    int new_y = m_dim.y / m_samplingRate;
    
    m_arrowCount = new_x * new_y;
    glm::vec2 vs[m_arrowCount];

    // set vertices as points on a grid, at grid square centers
    glm::vec2 tx_sz_ndc = 2.0f / glm::vec2(new_x, new_y);
    glm::vec2 center_offset = tx_sz_ndc * 0.5f;
    glm::vec2 coord = { -1.0f, -1.0f };
    //
    int idx = 0;
    for (int y = 0; y < new_y; y++)
    {
        coord.x = -1.0f;
        for (int x = 0; x < new_x; x++)
        {
            vs[idx++] = coord + center_offset;
            coord.x += tx_sz_ndc.x;

        }
        coord.y += tx_sz_ndc.y;

    }
    
    Ref<VertexBuffer> vbo = API::newVertexBuffer(GL_STATIC_DRAW);
    vbo->setData((void*)&(vs[0]), sizeof(glm::vec2) * m_arrowCount);
    vbo->setBufferLayout({
        { VERTEX_ATTRIB_LOCATION_POSITION, ShaderDataType::Float2, "a_position" },
    });

    m_vao = API::newVertexArray(vbo);

    //
    m_shader = ShaderLibrary::load("arrows2d_shader", "../assets/shaders/arrows2d.glsl");

    // calculate arrow size based on the vp and the lowest dim
    float min_dim = (float)(m_dim.x <= m_dim.y ? m_dim.x : m_dim.y);
    float min_dim_vp = (m_dim.x <= m_dim.y ? m_vp.x : m_vp.y);
    m_arrowSize = m_samplingRate * (min_dim_vp / min_dim);

}


