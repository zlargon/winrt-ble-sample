#include <iostream>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Devices.Enumeration.h>
#include <winrt/Windows.Devices.Bluetooth.h>
#include <winrt/Windows.Devices.Bluetooth.GenericAttributeProfile.h>
#include <cstdio>

using namespace winrt;
using namespace winrt::Windows::Devices::Enumeration;
using namespace winrt::Windows::Foundation;

event_token deviceWatcherAddedToken;
event_token deviceWatcherUpdatedToken;
event_token deviceWatcherRemovedToken;
event_token deviceWatcherEnumerationCompletedToken;
event_token deviceWatcherStoppedToken;

void DeviceWatcher_Added(DeviceWatcher sender, DeviceInformation deviceInfo);
void DeviceWatcher_Updated(DeviceWatcher sender, DeviceInformationUpdate deviceInfoUpdate);
void DeviceWatcher_Removed(DeviceWatcher sender, DeviceInformationUpdate deviceInfoUpdate);
void DeviceWatcher_EnumerationCompleted(DeviceWatcher sender, IInspectable const&);
void DeviceWatcher_Stopped(DeviceWatcher sender, IInspectable const&);

// main
int main () {
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
    deviceWatcherAddedToken   = deviceWatcher.Added(DeviceWatcher_Added);
    deviceWatcherUpdatedToken = deviceWatcher.Updated(DeviceWatcher_Updated);
    deviceWatcherRemovedToken = deviceWatcher.Removed(DeviceWatcher_Removed);
    deviceWatcherStoppedToken = deviceWatcher.Stopped(DeviceWatcher_Stopped);
    deviceWatcherEnumerationCompletedToken = deviceWatcher.EnumerationCompleted(DeviceWatcher_EnumerationCompleted);

    // Register event handlers before starting the watcher.
    // Clear existing devices
    printf("deviceWatcher.Start\n");
    deviceWatcher.Start();

    printf("end\n");
    return 0;
}


// 1. DeviceWatcher_Added
void DeviceWatcher_Added(DeviceWatcher sender, DeviceInformation deviceInfo)
{
    printf("DeviceWatcher_Added\n");
}

// 2. DeviceWatcher_Updated
void DeviceWatcher_Updated(DeviceWatcher sender, DeviceInformationUpdate deviceInfoUpdate)
{
    printf("DeviceWatcher_Updated\n");
}

// 3. DeviceWatcher_Removed
void DeviceWatcher_Removed(DeviceWatcher sender, DeviceInformationUpdate deviceInfoUpdate)
{
    printf("DeviceWatcher_Removed\n");
}

// 4. DeviceWatcher_EnumerationCompletedDeviceWatcher_EnumerationCompleted
void DeviceWatcher_EnumerationCompleted(DeviceWatcher sender, IInspectable const&)
{
    printf("DeviceWatcher_EnumerationCompleted\n");
}

// 5. DeviceWatcher_Stopped
void DeviceWatcher_Stopped(DeviceWatcher sender, IInspectable const&)
{
    printf("DeviceWatcher_Stopped\n");
}
