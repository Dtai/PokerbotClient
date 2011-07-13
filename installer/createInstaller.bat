del setup.msi
candle rc.wxs
light rc.wixobj -cultures:nl-be;en-us -ext WixUIExtension.dll -ext WixUtilExtension.dll
rename rc.msi setup.msi