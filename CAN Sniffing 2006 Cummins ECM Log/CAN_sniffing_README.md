

This Excel is a full CAN_bus sniffing of my 2006 Ram based 5.9 Cummins (common rail) engine ECM along
with a 2006 1500 Ram ABS module that is being used to supply the Cummins' ECM with the required data
for vehicle speed. This information was downloaded by using a Canny 7.2 Duo. The Canny is self
contained with all required components and functionality that make sniffing CAN packets quick and 
efficient. My main goal from this CAN_bus sniff, was to obtain the vehicle speed data (0x215) at 0 mph 
to mph++ value while the throttle pedal remain at idle until depressed slightly. This data helps with
 deciphering which byte/bit values are required for my project as well as future implementations.