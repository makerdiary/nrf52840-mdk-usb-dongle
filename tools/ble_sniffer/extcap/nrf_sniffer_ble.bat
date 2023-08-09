@echo off

rem Path to this batch file
set NRF_SNIFFER_BLE_PATH=%~dp0
rem Remove the "\" from the end of the path
set NRF_SNIFFER_BLE_PATH=%NRF_SNIFFER_BLE_PATH:~0,-1%

rem Activate virtualenv if present
if exist "%NRF_SNIFFER_BLE_PATH%\env\Scripts\activate.bat" call "%NRF_SNIFFER_BLE_PATH%\env\Scripts\activate.bat"

rem Find out if the launcher is installed and available
where py > NUL 2>&1 
if %ERRORLEVEL% EQU 0 (
    py -3 "%NRF_SNIFFER_BLE_PATH%\nrf_sniffer_ble.py" %*
) else (
    python "%NRF_SNIFFER_BLE_PATH%\nrf_sniffer_ble.py" %*
)
