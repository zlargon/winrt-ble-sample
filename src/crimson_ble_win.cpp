#include <iostream>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Devices.Enumeration.h>
#include <winrt/Windows.Devices.Bluetooth.h>
#include <winrt/Windows.Devices.Bluetooth.GenericAttributeProfile.h>
#include <cstdio>

using namespace winrt;
using namespace winrt::Windows::Devices::Enumeration;
using namespace winrt::Windows::Foundation;

int main () {
    DeviceWatcher deviceWatcher{ nullptr };

    // Property strings are documented here https://msdn.microsoft.com/en-us/library/windows/desktop/ff521659(v=vs.85).aspx
    auto requestedProperties = single_threaded_vector<hstring>({
        L"System.Devices.Aep.DeviceAddress",
        L"System.Devices.Aep.IsConnected",
        L"System.Devices.Aep.Bluetooth.Le.IsConnectable"
    });

    hstring aqsAllBluetoothLEDevices = L"(System.Devices.Aep.ProtocolId:=\"{bb7bb05e-5972-42b5-94fc-76eaa7084d49}\")";
    deviceWatcher = DeviceInformation::CreateWatcher(aqsAllBluetoothLEDevices,
                    requestedProperties,
                    DeviceInformationKind::AssociationEndpoint);

    // Register event handlers before starting the watcher.
    // Clear existing devices
    try {
        deviceWatcher.Start();
    } catch (winrt::hresult_error& e) { //got E_ILLEGAL_METHOD_CALL 0x8000000E
        printf("ERROR: scanning exception.\n");
        printf("CODE: %ld\n", (long) e.code());
        printf("MESSAGE: %s\n", e.message());
    }

}
