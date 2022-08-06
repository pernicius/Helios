#pragma once

#include "HeliosEngine/Core/Base.h"
//TODO:#include "HeliosEngine/Core/Timestep.h"
#include "HeliosEngine/Events/Event.h"


namespace HeliosEngine {


	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
//TODO		virtual void OnUpdate(Timestep ts) {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};


} //namespace HeliosEngine
