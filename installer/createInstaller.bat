del setup.msi
candle rc.wxs
light rc.wixobj -loc WixUI_nl-nl.wxl -ext WixUIExtension.dll -ext WixUtilExtension.dll
rename rc.msi setup.msi
cscript checkbox.js setup.msi