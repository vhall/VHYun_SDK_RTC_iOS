Pod::Spec.new do |s|
  s.name            = "VHYun_RTC"
  s.version         = "2.2.0"
  s.author          = { "wangxiaoxiang" => "xiaoxiang.wang@vhall.com" }
  s.license         = { :type => "MIT", :file => "LICENSE" }
  s.homepage        = 'https://www.vhall.com'
  s.source          = { :git => "https://github.com/vhall/VHYun_SDK_RTC_iOS.git", :tag => s.version.to_s}
  s.summary         = "iOS RTC framework"
  s.platform        = :ios, '8.0'
  s.requires_arc    = true
  #s.source_files    = ''
  s.frameworks      = 'Foundation'
  s.module_name     = 'VHYun_RTC'
  s.resources       = ['README.md']
  #s.resource_bundles= {}
  s.vendored_frameworks = 'VHYunFrameworks/*.framework'
  s.pod_target_xcconfig = {
    'FRAMEWORK_SEARCH_PATHS' => '$(inherited) $(PODS_ROOT)/**',
    'HEADER_SEARCH_PATHS' => '$(inherited) $(PODS_ROOT)/**'
  }

  s.dependency 'VHCore','>=2.0.3'
end
