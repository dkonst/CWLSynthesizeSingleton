Pod::Spec.new do |s|
  s.name         = "CWLSynthesizeSingleton"
  s.version      = "0.0.1"
  s.summary      = "Matt Gallagher's Singleton macro."
  s.homepage     = "https://github.com/incbee/CWLSynthesizeSingleton"
  s.license       = {
    :type => 'MIT',
    :text => 'Copyright 2012 by Incredible Bee.'
  }
  s.author       = { "Incredible Bee" => "email@address.com" }
  s.source       = { :git => "https://github.com/stephenzl/CWLSynthesizeSingleton.git" }
  s.platform     = :ios
  s.source_files = '*.{h,m}'
end
