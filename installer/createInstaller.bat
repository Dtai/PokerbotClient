del setup.msi
candle rc.wxs
light rc.wixobj -loc nl.wxl -ext WixUIExtension.dll -ext WixUtilExtension.dll
rename rc.msi setup.msi