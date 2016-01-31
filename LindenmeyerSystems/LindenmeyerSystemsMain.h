#pragma once

#include "Common\StepTimer.h"
#include "Common\DeviceResources.h"
#include "Content\Sample3DSceneRenderer.h"
#include "Content\SampleFpsTextRenderer.h"
#include "Content\LSystemObject.h"
#include "Content\LSystemInterpreter.h"

// Renders Direct2D and 3D content on the screen.
namespace LindenmeyerSystems
{
	class LindenmeyerSystemsMain : public DX::IDeviceNotify
	{
	public:
		LindenmeyerSystemsMain(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		~LindenmeyerSystemsMain();
		void CreateWindowSizeDependentResources();
		void Update();
		bool Render();

		// IDeviceNotify
		virtual void OnDeviceLost();
		virtual void OnDeviceRestored();

	private:

		void CreateLSystemContent();

		// Cached pointer to device resources.
		std::shared_ptr<DX::DeviceResources> m_deviceResources;

		// TODO: Replace with your own content renderers.
		std::unique_ptr<Sample3DSceneRenderer> m_sceneRenderer;
		std::unique_ptr<SampleFpsTextRenderer> m_fpsTextRenderer;

		// LSystem specific content
		std::shared_ptr<LSystemObject> m_testLSystem;
		std::shared_ptr<LSystemInterpreter> m_testInterpreter;

		// Rendering loop timer.
		DX::StepTimer m_timer;
	};
}