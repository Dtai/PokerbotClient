:: first get the DLL pack from:
:: https://github.com/Dtai/PokerbotClient/downloads 
:: (that is also the place to upload the new installer)

del setup.msi
candle rc.wxs
light rc.wixobj -loc WixUI_nl-nl.wxl -ext WixUIExtension.dll -ext WixUtilExtension.dll
rename rc.msi setup.msi
cscript checkbox.js setup.msi
