xcopy "..\Binarios\*.*" "output2\" /s /f /Y
xcopy "..\Arquivos_Profile\bin\*.*" "output2\" /s /f /Y
xcopy "..\Graficos\KIFONT.SP" "output2\" /s /f /Y
xcopy "..\Staff\STAFF.SP" "output2\" /s /f /Y
python kisindat_extractor.py r SLPS_008.99 KISINDAT.NCB .\output2
pause