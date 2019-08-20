#include <iostream>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Devices.Enumeration.h>
#include <winrt/Windows.Devices.Bluetooth.h>
#include <winrt/Windows.Devices.Bluetooth.GenericAttributeProfile.h>

using namespace winrt;
using namespace winrt::Windows::Devices::Enumeration;
using namespace winrt::Windows::Foundation;
using namespace std::chrono_literals;   // seconds

void DeviceWatcher_Added(DeviceWatcher sender, DeviceInformation deviceInfo);
void DeviceWatcher_Updated(DeviceWatcher sender, DeviceInformationUpdate deviceInfoUpdate);
void DeviceWatcher_Removed(DeviceWatcher sender, DeviceInformationUpdate deviceInfoUpdate);
void DeviceWatcher_EnumerationCompleted(DeviceWatcher sender, IInspectable const&);
void DeviceWatcher_Stopped(DeviceWatcher sender, IInspectable const&);

// main
int main () {
    winrt::init_apartment();

    std::cout << "Main Thread Id: " << std::this_thread::get_id() << std::endl;

    // BT_Code: Example showing paired and non-paired in a single query.
    hstring aqsAllBluetoothLEDevices = L"(System.Devices.Aep.ProtocolId:=\"{bb7bb05e-5972-42b5-94fc-76eaa7084d49}\")";

    // Property strings are documented here https://msdn.microsoft.com/en-us/library/windows/desktop/ff521659(v=vs.85).aspx
    auto requestedProperties = single_threaded_vector<hstring>({
        L"System.Devices.Aep.DeviceAddress",
        L"System.Devices.Aep.IsConnected",
        L"System.Devices.Aep.Bluetooth.Le.IsConnectable"
    });

    DeviceWatcher deviceWatcher = DeviceInformation::CreateWatcher(
        aqsAllBluetoothLEDevices,
        requestedProperties,
        DeviceInformationKind::AssociationEndpoint
    );

    // Register event handlers before starting the watcher.
    deviceWatcher.Added(DeviceWatcher_Added);       // must use
    deviceWatcher.Updated(DeviceWatcher_Updated);   // must use
    deviceWatcher.Removed(DeviceWatcher_Removed);
    deviceWatcher.Stopped(DeviceWatcher_Stopped);
    deviceWatcher.EnumerationCompleted(DeviceWatcher_EnumerationCompleted);

    // Register event handlers before starting the watcher.
    // Clear existing devices
    deviceWatcher.Start();

    // sleep 10s
    std::this_thread::sleep_for(10s);

    std::cout << "Done -- Main Thread Id: " << std::this_thread::get_id() << std::endl;
    return 0;
}


// 1. DeviceWatcher_Added
void DeviceWatcher_Added(DeviceWatcher sender, DeviceInformation deviceInfo)
{
    std::cout << "DeviceWatcher_Added (" << std::this_thread::get_id() << ") -- "
            << deviceInfo.Id().c_str() << " : " << deviceInfo.Name().c_str() << std::endl;
}

// 2. DeviceWatcher_Updated
void DeviceWatcher_Updated(DeviceWatcher sender, DeviceInformationUpdate deviceInfoUpdate)
{
    std::cout << "DeviceWatcher_Updated (" << std::this_thread::get_id() << ")" << std::endl;
}

// 3. DeviceWatcher_Removed
void DeviceWatcher_Removed(DeviceWatcher sender, DeviceInformationUpdate deviceInfoUpdate)
{
    std::cout << "DeviceWatcher_Removed (" << std::this_thread::get_id() << ")" << std::endl;
}

// 4. DeviceWatcher_EnumerationCompletedDeviceWatcher_EnumerationCompleted
void DeviceWatcher_EnumerationCompleted(DeviceWatcher sender, IInspectable const&)
{
    std::cout << "DeviceWatcher_EnumerationCompleted (" << std::this_thread::get_id() << ")" << std::endl;
}

// 5. DeviceWatcher_Stopped
void DeviceWatcher_Stopped(DeviceWatcher sender, IInspectable const&)
{
    std::cout << "DeviceWatcher_Stopped (" << std::this_thread::get_id() << ")" << std::endl;
}
