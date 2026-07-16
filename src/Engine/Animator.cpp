#include "Animator.hpp"
#include "../Settings.hpp"

RE::Animator::Animator(const char* path, Model* model) : m_index(0), m_frame(0), m_model(model)
{
    m_modelAnim = LoadModelAnimations(path, &m_count);

    m_animName.reserve(m_count);
    for (size_t i = 0; i < m_count; i++)
    {
        m_animName.emplace_back(m_modelAnim[i].name);
    }

    speed = Settings::d_animSpeed;
    m_current = m_animName[0];
}

void RE::Animator::update()
{
    m_frame += GetFrameTime() * speed;
    m_frame = fmodf(m_frame, m_modelAnim[m_index].keyframeCount);

    UpdateModelAnimation(*m_model, m_modelAnim[m_index], m_frame);
}

void RE::Animator::setCurrent(int index)
{
    m_index = index;
}

void RE::Animator::setCurrent(const char* name)
{
    for (size_t i = 0; i < m_count; i++)
    {
        if (name == m_modelAnim[i].name)
        {
            m_index = i;
            return;
        }
    }
    m_index = 0;
}

void RE::Animator::gui()
{ 
    
    if (m_count <= 0)
    {
        return;
    }

    ImGui::SeparatorText("Animation");
    ImGui::DragFloat("Speed", &speed, 0.1f);
   
    if (ImGui::BeginCombo("Animations", m_current))
    {
        for (int i = 0; i < m_animName.size(); i++)
        {
            bool selected = (m_current == m_animName[i]);
            if (ImGui::Selectable(m_animName[i], selected))
            {
                m_current = m_animName[i];
                m_index = i;
            }

            if (selected)
            {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }
}

