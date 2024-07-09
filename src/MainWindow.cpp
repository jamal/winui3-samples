#include "MainWindow.h"
#include <sstream>
#include <winrt/Microsoft.UI.Xaml.Input.h>

// void MainWindow::OnLaunched(
//     winrt::Microsoft::UI::Xaml::LaunchActivatedEventArgs const &args) {
void MainWindow::InitializeComponent() {
  using namespace winrt::Windows::Foundation;
  using namespace winrt::Microsoft::UI::Xaml;
  using namespace winrt::Microsoft::UI::Xaml::Controls;

  Title(L"WinUI3 Sample");

  auto compositor = Media::CompositionTarget::GetCompositorForCurrentThread();

  m_animation = compositor.CreateSpringVector3Animation();
  m_animation.Target(L"Scale");
  m_animation.DampingRatio(0.6f);
  m_animation.Period(TimeSpan{500000});

  updateText();

  auto panel = StackPanel{};
  panel.HorizontalAlignment(HorizontalAlignment::Center);
  panel.VerticalAlignment(VerticalAlignment::Center);
  panel.Spacing(10);

  auto button = Button{};
  button.Content(winrt::box_value(L"Press Me"));
  button.PointerEntered([this](IInspectable const &self,
                               Input::PointerRoutedEventArgs const &args) {
    m_animation.FinalValue(Numerics::float3(1.5, 1.5, 1.5));
    winrt::unbox_value<UIElement>(self).StartAnimation(m_animation);
  });
  button.PointerExited([this](IInspectable const &self,
                              Input::PointerRoutedEventArgs const &args) {
    m_animation.FinalValue(Numerics::float3(1.0, 1.0, 1.0));
    winrt::unbox_value<UIElement>(self).StartAnimation(m_animation);
  });
  button.Click([this](IInspectable const &self, RoutedEventArgs const &args) {
    m_count++;
    updateText();
  });

  panel.Children().Append(m_text);
  panel.Children().Append(button);
  Content(panel);
}

winrt::Microsoft::UI::Xaml::Markup::IXamlType MainWindow::GetXamlType(
    winrt::Windows::UI::Xaml::Interop::TypeName const &type) {
  return m_provider.GetXamlType(type);
}

winrt::Microsoft::UI::Xaml::Markup::IXamlType
MainWindow::GetXamlType(winrt::hstring const &fullname) {
  return m_provider.GetXamlType(fullname);
}

winrt::com_array<winrt::Microsoft::UI::Xaml::Markup::XmlnsDefinition>
MainWindow::GetXmlnsDefinitions() {
  return m_provider.GetXmlnsDefinitions();
}

void MainWindow::updateText() {
  std::wostringstream ss;
  ss << L"Pressed " << m_count << L" times";
  m_text.Text(ss.str());
}