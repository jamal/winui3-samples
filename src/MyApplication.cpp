#include "MyApplication.h"
#include "MainWindow.h"

MyApplication::MyApplication() {
  UnhandledException(
      [](winrt::Windows::Foundation::IInspectable const &,
         winrt::Microsoft::UI::Xaml::UnhandledExceptionEventArgs const &e) {
        // TODO
      });
}

void MyApplication::OnLaunched(
    winrt::Microsoft::UI::Xaml::LaunchActivatedEventArgs const &args) {
  m_window = winrt::make<MainWindow>();
  m_window.Activate();
}

winrt::Microsoft::UI::Xaml::Markup::IXamlType MyApplication::GetXamlType(
    winrt::Windows::UI::Xaml::Interop::TypeName const &type) {
  return m_provider.GetXamlType(type);
}

winrt::Microsoft::UI::Xaml::Markup::IXamlType
MyApplication::GetXamlType(winrt::hstring const &fullname) {
  return m_provider.GetXamlType(fullname);
}

winrt::com_array<winrt::Microsoft::UI::Xaml::Markup::XmlnsDefinition>
MyApplication::GetXmlnsDefinitions() {
  return m_provider.GetXmlnsDefinitions();
}