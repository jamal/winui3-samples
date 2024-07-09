#pragma once

#include "pch.h"

struct MyApplication
    : public winrt::Microsoft::UI::Xaml::ApplicationT<
          MyApplication,
          winrt::Microsoft::UI::Xaml::Markup::IXamlMetadataProvider> {

  MyApplication();

  void
  OnLaunched(winrt::Microsoft::UI::Xaml::LaunchActivatedEventArgs const &args);

  winrt::Microsoft::UI::Xaml::Markup::IXamlType
  GetXamlType(winrt::Windows::UI::Xaml::Interop::TypeName const &type);

  winrt::Microsoft::UI::Xaml::Markup::IXamlType
  GetXamlType(winrt::hstring const &fullname);

  winrt::com_array<winrt::Microsoft::UI::Xaml::Markup::XmlnsDefinition>
  GetXmlnsDefinitions();

private:
  winrt::Microsoft::UI::Xaml::Window m_window{nullptr};
  winrt::Microsoft::UI::Xaml::XamlTypeInfo::XamlControlsXamlMetaDataProvider
      m_provider;
};
