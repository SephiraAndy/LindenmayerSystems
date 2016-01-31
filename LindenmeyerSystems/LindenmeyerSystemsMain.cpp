#include "pch.h"
#include "LindenmeyerSystemsMain.h"
#include "Common\DirectXHelper.h"

using namespace LindenmeyerSystems;
using namespace Windows::Foundation;
using namespace Windows::System::Threading;
using namespace Concurrency;

// Loads and initializes application assets when the application is loaded.
LindenmeyerSystemsMain::LindenmeyerSystemsMain(const std::shared_ptr<DX::DeviceResources>& deviceResources) :
	m_deviceResources(deviceResources)
{
	// Register to be notified if the Device is lost or recreated
	m_deviceResources->RegisterDeviceNotify(this);

	// Create the LSystemStringBuilder object
	CreateLSystemContent();

	// TODO: Replace this with your app's content initialization.
	m_sceneRenderer = std::unique_ptr<Sample3DSceneRenderer>(new Sample3DSceneRenderer(m_deviceResources));

	m_fpsTextRenderer = std::unique_ptr<SampleFpsTextRenderer>(new SampleFpsTextRenderer(m_deviceResources));

	// TODO: Change the timer settings if you want something other than the default variable timestep mode.
	// e.g. for 60 FPS fixed timestep update logic, call:
	/*
	m_timer.SetFixedTimeStep(true);
	m_timer.SetTargetElapsedSeconds(1.0 / 60);
	*/
}

LindenmeyerSystemsMain::~LindenmeyerSystemsMain()
{
	// Deregister device notification
	m_deviceResources->RegisterDeviceNotify(nullptr);
}

// Updates application state when the window size changes (e.g. device orientation change)
void LindenmeyerSystemsMain::CreateWindowSizeDependentResources() 
{
	// TODO: Replace this with the size-dependent initialization of your app's content.
	m_sceneRenderer->CreateWindowSizeDependentResources();
}

// Updates the application state once per frame.
void LindenmeyerSystemsMain::Update() 
{
	// Update scene objects.
	m_timer.Tick([&]()
	{
		// TODO: Replace this with your app's content update functions.
		m_sceneRenderer->Update(m_timer);
		m_fpsTextRenderer->Update(m_timer);
	});
}

// Renders the current frame according to the current application state.
// Returns true if the frame was rendered and is ready to be displayed.
bool LindenmeyerSystemsMain::Render() 
{
	// Don't try to render anything before the first Update.
	if (m_timer.GetFrameCount() == 0)
	{
		return false;
	}

	auto context = m_deviceResources->GetD3DDeviceContext();

	// Reset the viewport to target the whole screen.
	auto viewport = m_deviceResources->GetScreenViewport();
	context->RSSetViewports(1, &viewport);

	// Reset render targets to the screen.
	ID3D11RenderTargetView *const targets[1] = { m_deviceResources->GetBackBufferRenderTargetView() };
	context->OMSetRenderTargets(1, targets, m_deviceResources->GetDepthStencilView());

	// Clear the back buffer and depth stencil view.
	context->ClearRenderTargetView(m_deviceResources->GetBackBufferRenderTargetView(), DirectX::Colors::CornflowerBlue);
	context->ClearDepthStencilView(m_deviceResources->GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	// Render the scene objects.
	// TODO: Replace this with your app's content rendering functions.
	m_sceneRenderer->Render();
	m_fpsTextRenderer->Render();

	return true;
}

// Notifies renderers that device resources need to be released.
void LindenmeyerSystemsMain::OnDeviceLost()
{
	m_sceneRenderer->ReleaseDeviceDependentResources();
	m_fpsTextRenderer->ReleaseDeviceDependentResources();
}

// Notifies renderers that device resources may now be recreated.
void LindenmeyerSystemsMain::OnDeviceRestored()
{
	m_sceneRenderer->CreateDeviceDependentResources();
	m_fpsTextRenderer->CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();
}

void LindenmeyerSystemsMain::CreateLSystemContent()
{
	// Create a new L-System object.
	m_testLSystem = std::shared_ptr<LSystemObject>(new LSystemObject());

	// Assign it an axiom and rule mapping.
	m_testLSystem->SetAxiom("X");
	m_testLSystem->AddRuleMapping('X', "F-[[X]+X]+F[+FX]-X");
	m_testLSystem->AddRuleMapping('F', "FF");
	
	// Set the L-System to a particular iteration/generation
	m_testLSystem->CacheInstructions(m_testLSystem->ComputeGeneration(3));

	// Set up how the characters are interpreted in a more human readable form.
	m_testInterpreter = std::shared_ptr<LSystemInterpreter>(new LSystemInterpreter());

	m_testInterpreter->AddInstructionMapping('F', Instruction::DrawForward);
	m_testInterpreter->AddInstructionMapping('-', Instruction::LeanLeft);
	m_testInterpreter->AddInstructionMapping('+', Instruction::LeanRight);
	m_testInterpreter->AddInstructionMapping('X', Instruction::DoNothing);
	m_testInterpreter->AddInstructionMapping('[', Instruction::OpenBranch);
	m_testInterpreter->AddInstructionMapping(']', Instruction::CloseBranch);

	// Unused in the current test but will be used later.
	m_testInterpreter->AddInstructionMapping('^', Instruction::BendForward);
	m_testInterpreter->AddInstructionMapping('v', Instruction::BendBack);

	// TODO: Generate geometry based on the LSystem described above.
}