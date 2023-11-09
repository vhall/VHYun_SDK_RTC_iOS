Pod::Spec.new do |s|
  s.name            = "VHYun_RTC"
  s.version         = "2.8.2"
  s.author          = { "GuoChao" => "chao.guo@vhall.com" }
  s.license         = { :type => "MIT", :file => "LICENSE" }
  s.homepage        = 'https://www.vhall.com'
  s.source          = { :git => "https://github.com/vhall/VHYun_SDK_RTC_iOS.git", :tag => s.version.to_s}
  s.summary         = "iOS RTC framework"
  s.platform        = :ios, '9.0'
  s.requires_arc    = true
  #s.source_files    = ''
  s.frameworks      = 'Foundation'
  s.module_name     = 'VHYun_RTC'
  s.resources       = ['README.md']
  #s.resource_bundles= {}
  s.vendored_frameworks = 'VHYunFrameworks/VHRTC.framework','VHYunFrameworks/VHWebRTC.framework'
  s.pod_target_xcconfig = {
    'FRAMEWORK_SEARCH_PATHS' => '$(inherited) $(PODS_ROOT)/**',
    'HEADER_SEARCH_PATHS' => '$(inherited) $(PODS_ROOT)/**',
    'VALID_ARCHS' => 'armv7 arm64',
  }

  s.dependency 'VHCore','>=2.3.5'
end
