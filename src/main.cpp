#include "pch.h"

#include <MddBootstrap.h>
#include <WindowsAppSDK-VersionInfo.h>
#include <winrt/Windows.UI.Xaml.Controls.h>

#include "MyApplication.h"

int WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int) {
  winrt::init_apartment(winrt::apartment_type::single_threaded);

  using namespace Microsoft::WindowsAppSDK;
  MddBootstrapInitialize2(Release::MajorMinor, Release::VersionTag,
                          PACKAGE_VERSION{Runtime::Version::UInt64},
                          MddBootstrapInitializeOptions_OnNoMatch_ShowUI);

  using namespace winrt::Microsoft::UI::Xaml;

  Application::Start([](auto &&) { winrt::make<MyApplication>(); });

  MddBootstrapShutdown();
  return 0;
};