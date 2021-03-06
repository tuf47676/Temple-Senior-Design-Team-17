s��        b�   � �  [H   �   ����                               agena                           Agilent ENA Series RF Network Analyzer      _VI_FUNC                                                  � � ��ViInt16  �  � ��ViInt32  � � ��ViReal64     � ��ViRsrc     	� 	��ViBoolean     	� 	��ViSession     � ��ViStatus     �  ViChar[]     � ��ViString     
�  	ViReal64[]  � � ��ViUInt32  � � ��ViUInt16     	�  ViInt16[]     	�  ViInt32[]     � 	 
ViBoolean[]     � ��ViConstString  w    This instrument module provides programming support for the Agilent ENA Series RF Network Analyzer. The module is divided into the following functions and classes:

Functions/Classes:

(1) Initialize:
This function initializes the instrument and sets it to a default configuration.

(2) Application Functions: (Class)
This class contains high-level, test and measurement routines.  These examples call other instrument driver functions to configure, start, and read from the instrument.

(3) Configuration Functions: (Class)
This class of functions configures the instrument by setting acquisition and system configuration parameters.

(4) Action/Status Functions: (Class)
This class of functions begins or terminates an acquisition. It also provides functions which allow the user to determine the current status of the instrument.

(5) Data Functions: (Class)
This class of functions transfers data to or from the instrument.

(6) Utility Functions: (Class)
This class of functions provides lower level functions to communicate with the instrument, and change instrument parameters.

(7) Close:
This function takes the instrument offline.
    �    This class contains high-level, test and measurement routines.  These examples call other instrument driver functions to configure, start, and read from the instrument.

Function:

(1) Application Example:
This function performs full 2-port calibration using the 85032F calibration kit, measures a band-pass filter (center frequency: 947.5 MHz), and calculates and displays its bandwidth, insertion loss, and so on.
     p    This class of functions configures the instrument by setting acquisition and system configuration parameters.
     G    This class of functions configures channel and trace for measurement.     5    This class of functions configures the sweep mode.
     8    This class of functions configures display parameters.     D    This class of functions provide function for setting calibration.
     7    This class of functions configures calibration kits.
     8    This class of functions configures power calibration.
     1    This class of functions configures limit test.
     1    This class of functions configures the marker.
     /    This class of functions configures analysis.
     C    This class of functions configures fixture simulator parameters.
     2    This class of functions configures time domain.
     ?    This class of functions configures transform of time domain.
     8    This class of functions configures system parameters.
     �    This class of functions begins or terminates an acquisition. It also provides functions which allow the user to determine the current status of the instrument.
     0    This class of functions clear averaging data.
     7    This class of functions updating or setting display.
     @    This class of functions starts the system-error calibrations.
     7    This class of functions starts the power calibration.     >    This class of functions starts the scalar-mixer calibration.     1    This class of functions starts or stops sweep.
     5    This class of functions provide marker operations.
     7    This class of functions provide analysis operations.
     :    This class of functions provide time domain operations.
     <    This class of functions provide file handling operations.
     5    This class of functions provide system operations.
     D    This class of functions transfers data to or from the instrument.
     :    This class of functions read or write calibration data.
     9    This class of functions provide limit test operations.
     5    This class of functions provide marker operations.
     9    This class of functions provide read or write IO data.
         This class of functions provides lower level functions to communicate with the instrument, and change instrument parameters.
    2    This function performs the following initialization actions:

- Opens a session to the Default Resource Manager resource and a session to the specified device using the interface and address specified in the Resource_Name control.

- Performs an identification query on the Instrument.

- Resets the instrument to a known state.

- Sends initialization commands to the instrument that set any necessary programmatic variables such as Headers Off, Short Command form, and Data Transfer Binary to the state necessary for the operation of the instrument driver.

- Returns an Instrument Handle which is used to differentiate between different sessions of this instrument driver.

- Each time this function is invoked a Unique Session is opened.  It is possible to have more than one session open for the same resource.
    )    This control specifies the interface and address of the device that is to be initialized (Instrument Descriptor). The exact grammar to be used in this control is shown in the note below. 

Default Value:  "GPIB::20"

Notes:

(1) Based on the Instrument Descriptor, this operation establishes a communication session with a device.  The grammar for the Instrument Descriptor is shown below.  Optional parameters are shown in square brackets ([]).

Interface   Grammar
------------------------------------------------------
GPIB        GPIB[board]::primary address[::secondary address]
            [::INSTR]
LAN         TCPIP::tcp/ip address::socket_number::SOCKET 
            
The GPIB keyword is used for GPIB interface.
The LAN  keyword is used for LAN interface.

Examples:
(1) GPIB   - "GPIB::20"
(2) LAN    - "TCPIP::192.168.1.33::5025::SOCKET"

The default value for optional parameters are shown below.

Optional Parameter          Default Value
-----------------------------------------
board                       0
secondary address           none - 31
    "    This control specifies if an ID Query is sent to the instrument during the initialization procedure.

Valid Range:
VI_FALSE (0) - Skip Query
VI_TRUE  (1) - Do Query (Default Value)

Notes:
   
(1) Under normal circumstances the ID Query ensures that the instrument initialized is the type supported by this driver. However circumstances may arise where it is undesirable to send an ID Query to the instrument.  In those cases; set this control to "Skip Query" and this function will initialize the selected interface, without doing an ID Query.    G    This control specifies if the instrument is to be reset to its power-on settings during the initialization procedure.

Valid Range:
VI_FALSE (0) - Don't Reset
VI_TRUE  (1) - Reset Device (Default Value)

Notes:

(1) If you do not want the instrument reset. Set this control to "Don't Reset" while initializing the instrument.    7    This control returns an Instrument Handle that is used in all subsequent function calls to differentiate between different sessions of this instrument driver.

Notes:

(1) Each time this function is invoked a Unique Session is opened.  It is possible to have more than one session open for the same resource.
    ;    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (ID Query) out of range.
BFFC0003  Parameter 3 (Reset Device) out of range.
BFFC0011  Instrument returned invalid response to ID Query

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
    w > %  �  �    Resource Name                     � > �       ID Query                          � >� �       Reset Device                      ! �Q �  }    Instrument Handle                 `����  �    Status                             "GPIB::20"  % Do Query VI_TRUE Skip Query VI_FALSE  * Reset Device VI_TRUE Don't Reset VI_FALSE    	           	           5    This function configure instrument for measurement.    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
    )    This control specifies the interface and address of the device that is to be initialized (Instrument Descriptor). The exact grammar to be used in this control is shown in the note below. 

Default Value:  "GPIB::20"

Notes:

(1) Based on the Instrument Descriptor, this operation establishes a communication session with a device.  The grammar for the Instrument Descriptor is shown below.  Optional parameters are shown in square brackets ([]).

Interface   Grammar
------------------------------------------------------
GPIB        GPIB[board]::primary address[::secondary address]
            [::INSTR]
LAN         TCPIP::tcp/ip address::socket_number::SOCKET 
            
The GPIB keyword is used for GPIB interface.
The LAN  keyword is used for LAN interface.

Examples:
(1) GPIB   - "GPIB::20"
(2) LAN    - "TCPIP::192.168.1.33::5025::SOCKET"

The default value for optional parameters are shown below.

Optional Parameter          Default Value
-----------------------------------------
board                       0
secondary address           none - 31
    "    This control specifies if an ID Query is sent to the instrument during the initialization procedure.

Valid Range:
VI_FALSE (0) - Skip Query
VI_TRUE  (1) - Do Query (Default Value)

Notes:
   
(1) Under normal circumstances the ID Query ensures that the instrument initialized is the type supported by this driver. However circumstances may arise where it is undesirable to send an ID Query to the instrument.  In those cases; set this control to "Skip Query" and this function will initialize the selected interface, without doing an ID Query.    G    This control specifies if the instrument is to be reset to its power-on settings during the initialization procedure.

Valid Range:
VI_FALSE (0) - Don't Reset
VI_TRUE  (1) - Reset Device (Default Value)

Notes:

(1) If you do not want the instrument reset. Set this control to "Don't Reset" while initializing the instrument.     �    This control sets the center frequency.

Valid Range:

E5061A
300.0e+3 to 1.5e+9 Hertz (Hz)

E5062A, E5070B
300.0e+3 to 3.0e+9 Hertz (Hz)

E5071B
300.0e+3 to 8.5e+9 Hertz (Hz)

Default Value: 9.475e+8 Hertz     �    This control sets the center frequency.

Valid Range:

E5061A
0.0 to 1.4997e+9 Hertz (Hz)

E5062A, E5070B
0.0 to 2.9997e+9 Hertz (Hz)

E5071B
0.0 to 8.4997e+9 Hertz (Hz)

Default Value: 2.0e+8 Hertz     s    Sets the IF bandwidth of selected channel.

Valid Range:
 10.0 to 100000.0 Hertz (Hz)

Default Value:
 1.0e+4 Hz
     �    Sets the power level of selected port of selected channel.

Valid Range:
E5061A, E5062A
   -45.0 dBm to  10.0 dBm

E5070B, E5071B
   -50.0 dBm to  10.0 dBm

Default Value:
-10.0 dBm    #d����  �    Status                            'e > %  �  �    Resource Name                     +� >) �       ID Query                          -� >� �       Reset Device                      / � % � d    Center Frequency [Hz]             /� � � � d    Span Frequency [Hz]               0� � � d    IF Bandwidth [Hz]                 12 �� � d    Power [dBm]                        	           "GPIB::20"  % Do Query VI_TRUE Skip Query VI_FALSE  * Reset Device VI_TRUE Don't Reset VI_FALSE    	9.475e+8    2.0e+8    1.0e+4    -10.0    �    This function performs open calibration for port 1 and port 2.

For this function you must set OPEN Port 1 and Port 2 on instrument.    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
    )    This control specifies the interface and address of the device that is to be initialized (Instrument Descriptor). The exact grammar to be used in this control is shown in the note below. 

Default Value:  "GPIB::20"

Notes:

(1) Based on the Instrument Descriptor, this operation establishes a communication session with a device.  The grammar for the Instrument Descriptor is shown below.  Optional parameters are shown in square brackets ([]).

Interface   Grammar
------------------------------------------------------
GPIB        GPIB[board]::primary address[::secondary address]
            [::INSTR]
LAN         TCPIP::tcp/ip address::socket_number::SOCKET 
            
The GPIB keyword is used for GPIB interface.
The LAN  keyword is used for LAN interface.

Examples:
(1) GPIB   - "GPIB::20"
(2) LAN    - "TCPIP::192.168.1.33::5025::SOCKET"

The default value for optional parameters are shown below.

Optional Parameter          Default Value
-----------------------------------------
board                       0
secondary address           none - 31
    "    This control specifies if an ID Query is sent to the instrument during the initialization procedure.

Valid Range:
VI_FALSE (0) - Skip Query
VI_TRUE  (1) - Do Query (Default Value)

Notes:
   
(1) Under normal circumstances the ID Query ensures that the instrument initialized is the type supported by this driver. However circumstances may arise where it is undesirable to send an ID Query to the instrument.  In those cases; set this control to "Skip Query" and this function will initialize the selected interface, without doing an ID Query.    G    This control specifies if the instrument is to be reset to its power-on settings during the initialization procedure.

Valid Range:
VI_FALSE (0) - Don't Reset
VI_TRUE  (1) - Reset Device (Default Value)

Notes:

(1) If you do not want the instrument reset. Set this control to "Don't Reset" while initializing the instrument.    4�����  �    Status                            8� > %  �  �    Resource Name                     <� >) �       ID Query                          ? >� �       Reset Device                       	           "GPIB::20"  % Do Query VI_TRUE Skip Query VI_FALSE  * Reset Device VI_TRUE Don't Reset VI_FALSE    �    This function performs short calibration for port 1 and port 2.

For this function you must set SHORT Port 1 and Port 2 on instrument.    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
    )    This control specifies the interface and address of the device that is to be initialized (Instrument Descriptor). The exact grammar to be used in this control is shown in the note below. 

Default Value:  "GPIB::20"

Notes:

(1) Based on the Instrument Descriptor, this operation establishes a communication session with a device.  The grammar for the Instrument Descriptor is shown below.  Optional parameters are shown in square brackets ([]).

Interface   Grammar
------------------------------------------------------
GPIB        GPIB[board]::primary address[::secondary address]
            [::INSTR]
LAN         TCPIP::tcp/ip address::socket_number::SOCKET 
            
The GPIB keyword is used for GPIB interface.
The LAN  keyword is used for LAN interface.

Examples:
(1) GPIB   - "GPIB::20"
(2) LAN    - "TCPIP::192.168.1.33::5025::SOCKET"

The default value for optional parameters are shown below.

Optional Parameter          Default Value
-----------------------------------------
board                       0
secondary address           none - 31
    "    This control specifies if an ID Query is sent to the instrument during the initialization procedure.

Valid Range:
VI_FALSE (0) - Skip Query
VI_TRUE  (1) - Do Query (Default Value)

Notes:
   
(1) Under normal circumstances the ID Query ensures that the instrument initialized is the type supported by this driver. However circumstances may arise where it is undesirable to send an ID Query to the instrument.  In those cases; set this control to "Skip Query" and this function will initialize the selected interface, without doing an ID Query.    G    This control specifies if the instrument is to be reset to its power-on settings during the initialization procedure.

Valid Range:
VI_FALSE (0) - Don't Reset
VI_TRUE  (1) - Reset Device (Default Value)

Notes:

(1) If you do not want the instrument reset. Set this control to "Don't Reset" while initializing the instrument.    B=����  �    Status                            F> > %  �  �    Resource Name                     Jo >) �       ID Query                          L� >� �       Reset Device                       	           "GPIB::20"  % Do Query VI_TRUE Skip Query VI_FALSE  * Reset Device VI_TRUE Don't Reset VI_FALSE    �    This function performs load calibration for port 1 and port 2.

For this function you must set LOAD Port 1 and Port 2 on instrument.    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
    )    This control specifies the interface and address of the device that is to be initialized (Instrument Descriptor). The exact grammar to be used in this control is shown in the note below. 

Default Value:  "GPIB::20"

Notes:

(1) Based on the Instrument Descriptor, this operation establishes a communication session with a device.  The grammar for the Instrument Descriptor is shown below.  Optional parameters are shown in square brackets ([]).

Interface   Grammar
------------------------------------------------------
GPIB        GPIB[board]::primary address[::secondary address]
            [::INSTR]
LAN         TCPIP::tcp/ip address::socket_number::SOCKET 
            
The GPIB keyword is used for GPIB interface.
The LAN  keyword is used for LAN interface.

Examples:
(1) GPIB   - "GPIB::20"
(2) LAN    - "TCPIP::192.168.1.33::5025::SOCKET"

The default value for optional parameters are shown below.

Optional Parameter          Default Value
-----------------------------------------
board                       0
secondary address           none - 31
    "    This control specifies if an ID Query is sent to the instrument during the initialization procedure.

Valid Range:
VI_FALSE (0) - Skip Query
VI_TRUE  (1) - Do Query (Default Value)

Notes:
   
(1) Under normal circumstances the ID Query ensures that the instrument initialized is the type supported by this driver. However circumstances may arise where it is undesirable to send an ID Query to the instrument.  In those cases; set this control to "Skip Query" and this function will initialize the selected interface, without doing an ID Query.    G    This control specifies if the instrument is to be reset to its power-on settings during the initialization procedure.

Valid Range:
VI_FALSE (0) - Don't Reset
VI_TRUE  (1) - Reset Device (Default Value)

Notes:

(1) If you do not want the instrument reset. Set this control to "Don't Reset" while initializing the instrument.    O�����  �    Status                            S� > %  �  �    Resource Name                     W� >) �       ID Query                          Z >� �       Reset Device                       	           "GPIB::20"  % Do Query VI_TRUE Skip Query VI_FALSE  * Reset Device VI_TRUE Don't Reset VI_FALSE    �    This function performs thru calibration between port 1 and port 2.

For this function you must set THRU between Port 1 and Port 2 on instrument.    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
    )    This control specifies the interface and address of the device that is to be initialized (Instrument Descriptor). The exact grammar to be used in this control is shown in the note below. 

Default Value:  "GPIB::20"

Notes:

(1) Based on the Instrument Descriptor, this operation establishes a communication session with a device.  The grammar for the Instrument Descriptor is shown below.  Optional parameters are shown in square brackets ([]).

Interface   Grammar
------------------------------------------------------
GPIB        GPIB[board]::primary address[::secondary address]
            [::INSTR]
LAN         TCPIP::tcp/ip address::socket_number::SOCKET 
            
The GPIB keyword is used for GPIB interface.
The LAN  keyword is used for LAN interface.

Examples:
(1) GPIB   - "GPIB::20"
(2) LAN    - "TCPIP::192.168.1.33::5025::SOCKET"

The default value for optional parameters are shown below.

Optional Parameter          Default Value
-----------------------------------------
board                       0
secondary address           none - 31
    "    This control specifies if an ID Query is sent to the instrument during the initialization procedure.

Valid Range:
VI_FALSE (0) - Skip Query
VI_TRUE  (1) - Do Query (Default Value)

Notes:
   
(1) Under normal circumstances the ID Query ensures that the instrument initialized is the type supported by this driver. However circumstances may arise where it is undesirable to send an ID Query to the instrument.  In those cases; set this control to "Skip Query" and this function will initialize the selected interface, without doing an ID Query.    G    This control specifies if the instrument is to be reset to its power-on settings during the initialization procedure.

Valid Range:
VI_FALSE (0) - Don't Reset
VI_TRUE  (1) - Reset Device (Default Value)

Notes:

(1) If you do not want the instrument reset. Set this control to "Don't Reset" while initializing the instrument.    ]A����  �    Status                            aB > %  �  �    Resource Name                     es >) �       ID Query                          g� >� �       Reset Device                       	           "GPIB::20"  % Do Query VI_TRUE Skip Query VI_FALSE  * Reset Device VI_TRUE Don't Reset VI_FALSE    �    This function performs thru calibration between port 2 and port 1.

For this function you must set THRU between Port 2 and Port 1 on instrument.    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
    )    This control specifies the interface and address of the device that is to be initialized (Instrument Descriptor). The exact grammar to be used in this control is shown in the note below. 

Default Value:  "GPIB::20"

Notes:

(1) Based on the Instrument Descriptor, this operation establishes a communication session with a device.  The grammar for the Instrument Descriptor is shown below.  Optional parameters are shown in square brackets ([]).

Interface   Grammar
------------------------------------------------------
GPIB        GPIB[board]::primary address[::secondary address]
            [::INSTR]
LAN         TCPIP::tcp/ip address::socket_number::SOCKET 
            
The GPIB keyword is used for GPIB interface.
The LAN  keyword is used for LAN interface.

Examples:
(1) GPIB   - "GPIB::20"
(2) LAN    - "TCPIP::192.168.1.33::5025::SOCKET"

The default value for optional parameters are shown below.

Optional Parameter          Default Value
-----------------------------------------
board                       0
secondary address           none - 31
    "    This control specifies if an ID Query is sent to the instrument during the initialization procedure.

Valid Range:
VI_FALSE (0) - Skip Query
VI_TRUE  (1) - Do Query (Default Value)

Notes:
   
(1) Under normal circumstances the ID Query ensures that the instrument initialized is the type supported by this driver. However circumstances may arise where it is undesirable to send an ID Query to the instrument.  In those cases; set this control to "Skip Query" and this function will initialize the selected interface, without doing an ID Query.    G    This control specifies if the instrument is to be reset to its power-on settings during the initialization procedure.

Valid Range:
VI_FALSE (0) - Don't Reset
VI_TRUE  (1) - Reset Device (Default Value)

Notes:

(1) If you do not want the instrument reset. Set this control to "Don't Reset" while initializing the instrument.    j�����  �    Status                            n� > %  �  �    Resource Name                     r� >) �       ID Query                          u% >� �       Reset Device                       	           "GPIB::20"  % Do Query VI_TRUE Skip Query VI_FALSE  * Reset Device VI_TRUE Don't Reset VI_FALSE       This function performs full 2-port calibration using the 85032F calibration kit, measures a band-pass filter (center frequency: 947.5 MHz), and calculates and displays its bandwidth, insertion loss, and so on.

For this function you must set DUT on instrument.    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     +    This control returns measured bandwidth.
     ?    This control returns center frequency of measured bandwidth.
     <    This control returns low frequency of measured bandwidth.
     <    This control returns high frequency of measured bandwidth.     :    This control returns the Q value of measured bandwidth.
     A    This control returns the loss parameter of measured bandwidth.
    )    This control specifies the interface and address of the device that is to be initialized (Instrument Descriptor). The exact grammar to be used in this control is shown in the note below. 

Default Value:  "GPIB::20"

Notes:

(1) Based on the Instrument Descriptor, this operation establishes a communication session with a device.  The grammar for the Instrument Descriptor is shown below.  Optional parameters are shown in square brackets ([]).

Interface   Grammar
------------------------------------------------------
GPIB        GPIB[board]::primary address[::secondary address]
            [::INSTR]
LAN         TCPIP::tcp/ip address::socket_number::SOCKET 
            
The GPIB keyword is used for GPIB interface.
The LAN  keyword is used for LAN interface.

Examples:
(1) GPIB   - "GPIB::20"
(2) LAN    - "TCPIP::192.168.1.33::5025::SOCKET"

The default value for optional parameters are shown below.

Optional Parameter          Default Value
-----------------------------------------
board                       0
secondary address           none - 31
    "    This control specifies if an ID Query is sent to the instrument during the initialization procedure.

Valid Range:
VI_FALSE (0) - Skip Query
VI_TRUE  (1) - Do Query (Default Value)

Notes:
   
(1) Under normal circumstances the ID Query ensures that the instrument initialized is the type supported by this driver. However circumstances may arise where it is undesirable to send an ID Query to the instrument.  In those cases; set this control to "Skip Query" and this function will initialize the selected interface, without doing an ID Query.    G    This control specifies if the instrument is to be reset to its power-on settings during the initialization procedure.

Valid Range:
VI_FALSE (0) - Don't Reset
VI_TRUE  (1) - Reset Device (Default Value)

Notes:

(1) If you do not want the instrument reset. Set this control to "Don't Reset" while initializing the instrument.    x�����  �    Status                            |� � % �  d    Bandwidth                         |� � � �  d    Center                            }@ � �  d    Low                               }� �� �  d    High                              }� � % �  d    Q                                 ~
 � � �  d    Loss                              ~S > %  �  �    Resource Name                     �� >) �       ID Query                          �� >� �       Reset Device                       	           	           	           	           	           	           	           "GPIB::20"  % Do Query VI_TRUE Skip Query VI_FALSE  * Reset Device VI_TRUE Don't Reset VI_FALSE    X    This function sets active channel and trace and configures parameters of active trace.    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Active Channel) out of range.
BFFC0003  Parameter 3 (Active Trace) out of range.
BFFC0005  Parameter 5 (Measurement Parameter) out of range.
BFFC0006  Parameter 6 (Data Format) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None    m    Set one of channel1 to channel(4)16 to the active channel.

Notes:
You can set only the displayed channel to the active channel. If you execute this command trying to set a not displayed channel to the active channel, an error occurs and the command is ignored.

Valid Range:
1 to 16    (for ENA E5070B/E5071B)
1 to 4     (for ENA E5061A/E5062A)

Default Value:
1     �    Set trace1 to trace(4)16 of active channel to the active trace.

Valid Range:
1 to 16    (for ENA R5070B/E5071B)
1 to 4     (for ENA E5061A/E5062A)

Default Value:
1     �    Sets number of traces of active channel.

Valid Range:
1 to upper limit setting for channel per trace number.

Default Value:
1    M    Selects the data format of the active trace of active channel.

Valid Values:
AGENA_FORMAT_LOG_MAGNITUDE (0)
  - Logarithmic magnitude format

AGENA_FORMAT_PHASE (1)
  - Phase format

AGENA_FORMAT_GROUP_DELAY (2)
  - Group delay format

AGENA_FORMAT_SMITH_LINEAR (3)
  - Smith chart format (Lin/Phase)

AGENA_FORMAT_SMITH_LOGARITHMIC (4)
  - Smith chart format (Log/Phase)

AGENA_FORMAT_SMITH_COMPLEX (5)
  - Smith chart format (Real/Imag)

AGENA_FORMAT_SMITH_IMPEDANCE (6)
  - Smith chart format (R+jX)

AGENA_FORMAT_SMITH_ADMITTANCE (7)
  - Smith chart format (G+jB)

AGENA_FORMAT_POLAR_LINEAR (8)
  - Polar format (Lin)

AGENA_FORMAT_POLAR_LOGARITHMIC (9)
  - Polar format (Log)

AGENA_FORMAT_POLAR_COMPLEX (10)
  - Polar format (Re/Im)

AGENA_FORMAT_LINEAR_MAGNITUDE (11)
  - Linear magnitude format

AGENA_FORMAT_SWR (12)
  - SWR format

AGENA_FORMAT_REAL (13)
  - Real format

AGENA_FORMAT_IMAGINARY (14)
  - Imaginary format

AGENA_FORMAT_EXPANDED_PHASE (15)
  - Expanded phase format

AGENA_FORMAT_POSITIVE_PHASE (16)
  - Positive phase format

Default Value:
AGENA_FORMAT_LOG_MAGNITUDE (0)
    �    Sets the measurement parameter of active channel and active trace.

Valid Values:
AGENA_MEASUREMENT_PARAMETER_S11  (0) - Specifies S11
AGENA_MEASUREMENT_PARAMETER_S21  (1) - Specifies S21
AGENA_MEASUREMENT_PARAMETER_S31  (2) - Specifies S31
AGENA_MEASUREMENT_PARAMETER_S41  (3) - Specifies S41
AGENA_MEASUREMENT_PARAMETER_S12  (4) - Specifies S12
AGENA_MEASUREMENT_PARAMETER_S22  (5) - Specifies S22
AGENA_MEASUREMENT_PARAMETER_S32  (6) - Specifies S32
AGENA_MEASUREMENT_PARAMETER_S42  (7) - Specifies S42
AGENA_MEASUREMENT_PARAMETER_S13  (8) - Specifies S13
AGENA_MEASUREMENT_PARAMETER_S23  (9) - Specifies S23
AGENA_MEASUREMENT_PARAMETER_S33 (10) - Specifies S33
AGENA_MEASUREMENT_PARAMETER_S43 (11) - Specifies S43
AGENA_MEASUREMENT_PARAMETER_S14 (12) - Specifies S14
AGENA_MEASUREMENT_PARAMETER_S24 (13) - Specifies S24
AGENA_MEASUREMENT_PARAMETER_S34 (14) - Specifies S34
AGENA_MEASUREMENT_PARAMETER_S44 (15) - Specifies S44

when the absolute measurement is executed:
AGENA_MEASUREMENT_PARAMETER_A   (16) - Specifies A
AGENA_MEASUREMENT_PARAMETER_B   (17) - Specifies B
AGENA_MEASUREMENT_PARAMETER_C   (18) - Specifies C
AGENA_MEASUREMENT_PARAMETER_D   (19) - Specifies D
AGENA_MEASUREMENT_PARAMETER_R1  (20) - Specifies R1
AGENA_MEASUREMENT_PARAMETER_R2  (21) - Specifies R2
AGENA_MEASUREMENT_PARAMETER_R3  (22) - Specifies R3
AGENA_MEASUREMENT_PARAMETER_R4  (23) - Specifies R4

Default Value:
AGENA_MEASUREMENT_PARAMETER_S11  (0)

Notes:
(1) ENA E5061A/E5062A supports only this values: S11, S21, S12, S22.
    �&����  �    Status                            �� %  �  �    Instrument Handle                 �� > % �  d    Active Channel                    � > � �  d    Active Trace                      �� >� �  d    Number Of Traces                  �J � � � �    Data Format                       �� � % � d    Measurement Parameter              	               1    1    1              �Logarithmic Magnitude AGENA_FORMAT_LOG_MAGNITUDE Phase AGENA_FORMAT_PHASE Group Delay AGENA_FORMAT_GROUP_DELAY Smith Linear AGENA_FORMAT_SMITH_LINEAR Smith Logarithmic AGENA_FORMAT_SMITH_LOGARITHMIC Smith Complex AGENA_FORMAT_SMITH_COMPLEX Smith Impedance AGENA_FORMAT_SMITH_IMPEDANCE Smith Admittance AGENA_FORMAT_SMITH_ADMITTANCE Polar Linear AGENA_FORMAT_POLAR_LINEAR Polar Logarithmic AGENA_FORMAT_POLAR_LOGARITHMIC Polar Complex AGENA_FORMAT_POLAR_COMPLEX Linear Magnitude AGENA_FORMAT_LINEAR_MAGNITUDE SWR AGENA_FORMAT_SWR Real AGENA_FORMAT_REAL Imaginary AGENA_FORMAT_IMAGINARY Expanded Phase AGENA_FORMAT_EXPANDED_PHASE Positive Phase AGENA_FORMAT_POSITIVE_PHASE              HS11 AGENA_MEASUREMENT_PARAMETER_S11 S21 AGENA_MEASUREMENT_PARAMETER_S21 S31 AGENA_MEASUREMENT_PARAMETER_S31 S41 AGENA_MEASUREMENT_PARAMETER_S41 S12 AGENA_MEASUREMENT_PARAMETER_S12 S22 AGENA_MEASUREMENT_PARAMETER_S22 S32 AGENA_MEASUREMENT_PARAMETER_S32 S42 AGENA_MEASUREMENT_PARAMETER_S42 S13 AGENA_MEASUREMENT_PARAMETER_S13 S23 AGENA_MEASUREMENT_PARAMETER_S23 S33 AGENA_MEASUREMENT_PARAMETER_S33 S43 AGENA_MEASUREMENT_PARAMETER_S43 S14 AGENA_MEASUREMENT_PARAMETER_S14 S24 AGENA_MEASUREMENT_PARAMETER_S24 S34 AGENA_MEASUREMENT_PARAMETER_S34 S44 AGENA_MEASUREMENT_PARAMETER_S44 A AGENA_MEASUREMENT_PARAMETER_A B AGENA_MEASUREMENT_PARAMETER_B C AGENA_MEASUREMENT_PARAMETER_C D AGENA_MEASUREMENT_PARAMETER_D R1 AGENA_MEASUREMENT_PARAMETER_R1 R2 AGENA_MEASUREMENT_PARAMETER_R2 R3 AGENA_MEASUREMENT_PARAMETER_R3 R4 AGENA_MEASUREMENT_PARAMETER_R4    +    This function configures power settings.
    `    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Port) out of range.
BFFC0004  Parameter 4 (Port Coupling) out of range.
BFFC0005  Parameter 5 (Auto Power Range) out of range.
BFFC0007  Parameter 7 (Power Slope) out of range.
BFFC0008  Parameter 8 (Power Slope Coefficient) out of range.
BFFC0009  Parameter 9 (Power Level) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Selects the corresponding channel.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA E5061A/E5062A)

Default Value: 1     �    Selects active port.

Valid Range:
0 to 4

Default Value:
1


Notes:
If port = 0, apply power level for all port command, otherwise use power level for each port function.    Y    Sets whether to output the same power level for each port of selected channel. When the power slope feature is on, the same power level is always outputted to all ports regardless of this setting because different power levels cannot be outputted for
each port.

Valid Values:
VI_TRUE  (1) - On
VI_FALSE (0) - Off

Default Value:
VI_TRUE  (1)
    p    Sets whether to turn ON or OFF the Auto Power Range set function of selected channel. When the Auto Power Range set function is ON, an attenuator level and a power range are selected automatically according to a maximum frequency and a maximum output power level as following figures.

Valid Values:
VI_TRUE  (1) - On
VI_FALSE (0) - Off

Default Value:
VI_FALSE (0)
    �    Sets the power range of selected channel.
The power range is selected depending on the setting of the attenuator. The following table shows the relationship between the attenuator value and the power range.
When Auto Power Range set function is effective, this command is ignored and an attenuator level and a power range are selected automatically acording to a maximum frequency and a maximum setting power.

Valid Range:

------------------------------------------------------------
 Attenuator |  Power range   | Attenuator |  Power range   |
------------|----------------|------------|----------------|
     0 dB   | -20 to +12 dBm |     5 dB   | -25 to  +7 dBm |
    10 dB   | -30 to  +2 dBm |    15 dB   | -35 to  -3 dBm |
    20 dB   | -40 to  -8 dBm |    25 dB   | -45 to -13 dBm |
    30 dB   | -50 to -18 dBm |    35 dB   | -55 to -23 dBm |
------------|----------------|------------|----------------|

Default Value:
0.0

Notes:
Applies only if Auto Power Range is set to OFF.
        Turns on/off the power slope feature of selected channel.
This function is a function to correct the attenuation of simple power level proportional to the frequency (attenuation due to cables and so on).

Valid Value:
VI_TRUE  (1) - On
VI_FALSE (0) - Off

Default Value:
VI_FALSE (0)
     |    Sets the correction value of the power slope feature of selected channel.

Valid Range:
 -2.0 to 2.0

Default Value:
 0.0
     �    Sets the power level of selected port of selected channel.

Valid Range:
  E5061A, E5062A
    -45.0 dBm to  10.0 dBm

  E5070B, E5071B
    -50.0 dBm to  10.0 dBm

Default Value:
0.0    �_����  �    Status                            �� %  �  �    Instrument Handle                 �f >  �  d    Channel                           � > � �  d    Port                              �� > �       Port Coupling                     � >s �       Auto Power Range                  �� >� �  d    Power Range                       �z � % �       Power Slope                       �� � p �  d    Power Slope Coefficient           �$ � � �  d    Power Level                        	               1    1   On VI_TRUE Off VI_FALSE    On VI_TRUE Off VI_FALSE    0.0    On VI_TRUE Off VI_FALSE    0.0    0.0    M    This function sets the fixed frequency (CW frequency) for the power sweep.
    (    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None        Sets the fixed frequency (CW frequency) for the power sweep for selected channel.

Units: Hertz (Hz)

Valid Range:

E5061A
300.0e+3 to 1.5e+9 Hertz (Hz)

E5062A, E5070B
300.0e+3 to 3.0e+9 Hertz (Hz)

E5071B
300.0e+3 to 8.5e+9 Hertz (Hz)

Default Value:
300.0e+3 Hertz
     �    Selects the corresponding channel.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA E5061A/E5062A)

Default Value: 1    ������  �    Status                            �� %  �  �    Instrument Handle                 �� > � �  d    Fixed Frequency                   �� > % �  d    Channel                            	               	300000.0    1    ,    This function configure sweep parameters.
    n    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Number Of Measurement Points) out of range.
BFFC0004  Parameter 4 (Delay Time) out of range.
BFFC0005  Parameter 5 (Sweep Type) out of range.
BFFC0006  Parameter 6 (Sweep Mode) out of range.
BFFC0007  Parameter 7 (Auto Sweep Time) out of range.
BFFC0009  Parameter 9 (Spurious Avoid Mode) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Sets whether to automatically set the sweep time of selected channel.

Valid Values:
VI_TRUE  (1) - On
VI_FALSE (0) - Off

Default Value:
VI_FALSE (0)
    +    Sets the sweep type of selected channel.

Valid Values:
AGENA_SWEEP_TYPE_LINEAR      (0) - Linear sweep
AGENA_SWEEP_TYPE_LOGARITHMIC (1) - Logarithmic sweep
AGENA_SWEEP_TYPE_SEGMENT     (2) - Segment sweep
AGENA_SWEEP_TYPE_POWER       (3) - Power sweep

Default Value:
AGENA_SWEEP_TYPE_LINEAR (0)
     �    Selects the corresponding channel.

Valid Range: 1 to 16     (for ENA E5070B/E5071B)
             1 to 4      (for ENA E5061A/E5062A)

Default Value: 1    >    Sets the number of measurement points of selected channel.

Valid Range:
2 to 1601

Default Value:
201

Notes:
If the specified parameter is out of the allowable setup range, the minimum value (if the lower limit of the range is not reached) or the maximum value (if the upper limit of the range is exceeded) is set.     x    Sets the sweep delay time of selected channel.

Units: seconds

Valid Range:
0.0 to 1.0 seconds

Default Value:
0.001
    �    Selects the sweep mode of selected channel.

When the sweep type is the power sweep, when the power calibration is on, or the power slope value is
other than 0 and the power slope function is on, if you execute this command to try to set the sweep mode to the swept mode or the fast swept mode, an error occurs and the sweep mode is automatically set to the step mode or the fast step mode, respectively.

Valid Values:
AGENA_SWEEP_MODE_STEPPED  (0) - Stepped mode
AGENA_SWEEP_MODE_ANALOG   (1) - Swept mode
AGENA_SWEEP_MODE_FSTEPPED (2) - Fast stepped mode
AGENA_SWEEP_MODE_FANALOG  (3) - Fast swept mode

Default Value:
AGENA_SWEEP_MODE_STEPPED  (0)

Notes:

(1) This control is ignored for ENA E5061A/E5062A.
    �    Sets the sweep time of selected channel.

Valid Range:
Varies depending on the measurement conditions.

Default Value:
0.001

Notes:
When the auto setting of the sweep time is ON, even if you try to set the sweep time to any value with this command, it automatically returns to the value defined by the E5070B/E5071B. Before using this command, turns OFF the auto setting of the sweep time.     �    For selected channel, enables or disables the spurious avoidance
mode.

Valid Values:
VI_TRUE  (1) - Enable
VI_FALSE (0) - Disable

Default Value:
VI_TRUE (1)

Notes:

(1) This control is ignored for ENA E5061A/E5062A.
    �w����  �    Status                            �� %  �  �    Instrument Handle                 Č �D �       Auto Sweep Time                   �- � % � d    Sweep Type                        �` > % �  d    Channel                           � > � �  d    Number Of Measurement Points      �G >� �  d    Delay Time                        �� � � � d    Sweep Mode                        ˙ �� �  d    Sweep Time                        �) � = �  `    Spurious Avoid Mode                	               On VI_TRUE Off VI_FALSE               �Linear AGENA_SWEEP_TYPE_LINEAR Logarithmic AGENA_SWEEP_TYPE_LOGARITHMIC Segment AGENA_SWEEP_TYPE_SEGMENT Power AGENA_SWEEP_TYPE_POWER    1    201    0.001               �Stepped AGENA_SWEEP_MODE_STEPPED Swept AGENA_SWEEP_MODE_ANALOG Fast Stepped AGENA_SWEEP_MODE_FSTEPPED Fast Swept AGENA_SWEEP_MODE_FANALOG    0.001    Enable VI_TRUE Disable VI_FALSE    @    This function sets frequency, power or time sweep parameters.
    	    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Signal Output) out of range.
BFFC0003  Parameter 4 (Stimulus) out of range.
BFFC0004  Parameter 5 (Parameter) out of range.
BFFC0005  Parameter 6 (Unit) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Selects parameter to define.

Valid Values:
AGENA_STIMULUS_START  (0) - Start
AGENA_STIMULUS_STOP   (1) - Stop
AGENA_STIMULUS_CENTER (2) - Center
AGENA_STIMULUS_SPAN   (3) - Span

Default Value:
AGENA_STIMULUS_START (0)
    �    Defines parameter for selected function.

Valid Range:
For Frequency Sweep:

------------------------------------
        |          E5061A          |
------------------------------------
Start   | 300.0 kHz to   1.5 GHz   |
Stop    | 300.0 kHz to   1.5 GHz   |
Center  | 300.0 kHz to   1.5 GHz   | 
Span    |   0.0  Hz to 1.4997 GHz  |
------------------------------------

------------------------------------
        |      E5062A, E5070B      |
------------------------------------
Start   | 300.0 kHz to   3.0 GHz   |
Stop    | 300.0 kHz to   3.0 GHz   |
Center  | 300.0 kHz to   3.0 GHz   | 
Span    |   0.0  Hz to 2.9997 GHz  |
------------------------------------

------------------------------------
        |          E5071B          |
------------------------------------
Start   | 300.0 kHz to   8.5 GHz   |
Stop    | 300.0 kHz to   8.5 GHz   |
Center  | 300.0 kHz to   8.5 GHz   | 
Span    |   0.0  Hz to 8.4997 GHz  |
------------------------------------


For Power Sweep:

------------------------------------
        |      E5061A, E5062A      |
------------------------------------
Start   | -45.0 dBm to  10.0 dBm   |
Stop    | -45.0 dBm to  10.0 dBm   |
Center  | -45.0 dBm to  10.0 dBm   | 
Span    |   0.0 dBm to  55.0 dBm   |
------------------------------------

------------------------------------
        |      E5070B, E5071B      |
------------------------------------
Start   | -50.0 dBm to  10.0 dBm   |
Stop    | -50.0 dBm to  10.0 dBm   |
Center  | -50.0 dBm to  10.0 dBm   | 
Span    |   0.0 dBm to  60.0 dBm   |
------------------------------------

For Time Sweep:

Varies depending on the measurement conditions.
AGENA_STIMULUS_PARAMETER_TIME_AUTO (-1) - automatically set the sweep time

Default Value: 0.0
    �    Selects the unit of parameter.

Valid Values:
AGENA_STIMULUS_UNITS_HZ  (0) -  Hz
AGENA_STIMULUS_UNITS_KHZ (1) - kHz
AGENA_STIMULUS_UNITS_MHZ (2) - MHz
AGENA_STIMULUS_UNITS_GHZ (3) - GHz
AGENA_STIMULUS_UNITS_DBM (4) - dBm
AGENA_STIMULUS_UNITS_DB  (5) - dB
AGENA_STIMULUS_UNITS_S   (6) - s 

Default Value: AGENA_STIMULUS_UNITS_HZ  (0)

Note:

(1) For correct setting use units Hz, kHz, MHz and GHz only if coresponding channel is using frequency sweep. For Power sweep use units dBm.
     �    Selects the corresponding channel.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA E5061A/E5062A)

Default Value: 1
     l    Sets the signal output. 

Valid Values:
VI_TRUE  (1) - On
VI_FALSE (0) - Off

Default Value:
VI_FALSE (0)
    �����  �    Status                            � %  �  �    Instrument Handle                 ײ � % � d    Stimulus                          ؘ � � � d    Parameter                         �t �� � d    Unit                              �a > % � d    Channel                           � > � �       Signal Output                      	                          jStart AGENA_STIMULUS_START Stop AGENA_STIMULUS_STOP Center AGENA_STIMULUS_CENTER Span AGENA_STIMULUS_SPAN    0.0               �Hz AGENA_STIMULUS_UNITS_HZ kHz AGENA_STIMULUS_UNITS_KHZ MHz AGENA_STIMULUS_UNITS_MHZ GHz AGENA_STIMULUS_UNITS_GHZ dBm AGENA_STIMULUS_UNITS_DBM dB AGENA_STIMULUS_UNITS_DB s AGENA_STIMULUS_UNITS_S    1    On VI_TRUE Off VI_FALSE    �    This function load sweep segments into instrument.

Notes:
If you disable some parameter you can pass NULL for corresponding array.
    ]    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Stimulus Mode) out of range.
BFFC0004  Parameter 4 (IF Bandwidth Enabled) out of range.
BFFC0005  Parameter 5 (Power Enabled) out of range.
BFFC0006  Parameter 6 (Sweep Delay Time Enabled) out of range.
BFFC0007  Parameter 7 (Sweep Mode Enabled) out of range.
BFFC0008  Parameter 8 (Sweep Time Enabled) out of range.
BFFC0009  Parameter 9 (Number of Segments) out of range.
BFFC0010  Parameter 10 (Start) is NULL pointer.
BFFC0011  Parameter 11 (Stop) is NULL pointer.
BFFC0012  Parameter 12 (Measurement points) is NULL pointer.
BFFC0013  Parameter 13 (IF Bandwidth) is NULL pointer.
BFFC0014  Parameter 14 (Power) is NULL pointer.
BFFC0015  Parameter 15 (Sweep Delay Time) is NULL pointer.
BFFC0016  Parameter 16 (Sweep Mode) is NULL pointer.
BFFC0017  Parameter 17 (Sweep Time) is NULL pointer.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Selects the corresponding channel.

Valid Range: 1 to 16     (for ENA E5070B/E5071B)
             1 to 4      (for ENA E5061A/E5062A)

Default Value: 1
     �    Sets stimulus setting mode.

Valid Values:
AGENA_SWEEP_SEGMENT_MODE_START  (0) - Start/Stop values
AGENA_SWEEP_SEGMENT_MODE_CENTER (1) - Center/Span values

Default Value:
AGENA_SWEEP_SEGMENT_MODE_START  (0)
     �    Enables or disables the IF bandwidth setting for each segment.

Valid Values:
VI_TRUE  (1) - Enables
VI_FALSE (0) - Disables

Default Value:
VI_FALSE (0)
     �    Enables or disables the power setting for each segment.

Valid Values:
VI_TRUE  (1) - Enables
VI_FALSE (0) - Disables

Default Value:
VI_FALSE (0)
     �    Enables or disables the sweep delay time setting for each segment.

Valid Values:
VI_TRUE  (1) - Enables
VI_FALSE (0) - Disables

Default Value:
VI_FALSE (0)
     �    Enables or disables the sweep mode setting for each segment.

Valid Values:
VI_TRUE  (1) - Enables
VI_FALSE (0) - Disables

Default Value:
VI_FALSE (0)
     �    Enables or disables the sweep time setting for each segment.

Valid Values:
VI_TRUE  (1) - Enables
VI_FALSE (0) - Disables

Default Value:
VI_FALSE (0)
     D    Sets number of segments.

Valid Range:
1 to 201

Default Value:
1
     �    Pass array of start or center values.

Notes:
(1) Number of elements must be equal as value in Number of Segments control.
(2) Type of values is specified in Stimulus Mode control.     �    Pass array of stop or span values.

Notes:
(1) Number of elements must be equal as value in Number of Segments control.
(2) Type of values is specified in Stimulus Mode control.
     �    Pass array of number of measurement points.

Notes:
(1) Number of elements must be equal as value in Number of Segments control.
     �    Pass array of IF bandwidth.

Notes:
(1) Number of elements must be equal as value in Number of Segments control.
(2) Not required (you can pass NULL) when the IF bandwidth setting for each segment is disabled.
     �    Pass array of power.

Notes:
(1) Number of elements must be equal as value in Number of Segments control.
(2) Not required (you can pass NULL) when the power setting for each segment is disabled.
     �    Pass array of sweep delay time.

Notes:
(1) Number of elements must be equal as value in Number of Segments control.
(2) Not required (you can pass NULL) when the sweep delay time setting for each segment is disabled.
     �    Pass array of sweep mode.

Notes:
(1) Number of elements must be equal as value in Number of Segments control.
(2) Not required (you can pass NULL) when the sweep mode setting for each segment is disabled.
        Pass array of sweep time.

Notes:
(1) Number of elements must be equal as value in Number of Segments control.
(2) Not required (you can pass NULL) when the sweep time setting for each segment is disabled.
(3) Specify 0 If you want to set "auto setting".
    ������  �    Status                            �] %  �  �    Instrument Handle                 �� ! % �  d    Channel                           � ! � � d    Stimulus Mode                     �x !7 �       IF Bandwidth Enabled              � !� �       Power Enabled                     � X > �       Sweep Delay Time Enabled          �a X � �       Sweep Mode Enabled                � X7 �       Sweep Time Enabled                � X� �  d    Number of Segments                �� � % 	�  d    Start/Center                      � � � 
�  d    Stop/Span                         �k � �  d    Measurement points                �� �� �  d    IF Bandwidth                      �� � % �  d    Power                             �� � � �  d    Sweep Delay Time                  �� � �  d    Sweep Mode                        �\ �� �  d    Sweep Time                         	               1               VStart/Stop AGENA_SWEEP_SEGMENT_MODE_START Center/Span AGENA_SWEEP_SEGMENT_MODE_CENTER     Enable VI_TRUE Disable VI_FALSE     Enable VI_TRUE Disable VI_FALSE     Enable VI_TRUE Disable VI_FALSE     Enable VI_TRUE Disable VI_FALSE     Enable VI_TRUE Disable VI_FALSE    1                                    0    This function configure IF bandwidth setting.
    [    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (IF Bandwidth) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     u    Sets the IF bandwidth of selected channel.

Valid Range:
 10.0 to 100000.0 Hertz (Hz)

Default Value:
 100000.0 Hz
     �    Selects the corresponding channel.

Valid Range: 1 to 16     (for ENA E5070B/E5071B)
             1 to 4      (for ENA E5061A/E5062A)

Default Value: 1
    ������  �    Status                            %  �  �    Instrument Handle                � > � �  d    IF Bandwidth                     $ > % �  d    Channel                            	               	100000.0    1    7    This function configure averaging of active channel.
    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (State) out of range.
BFFC0004  Parameter 4 (Factor) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Enables or disables the averaging of active channel.

Valid Values:
VI_TRUE  (1) - On
VI_FALSE (0) - Off

Default Value:
VI_FALSE (0)
     Y    Sets the averaging factor of active channel.

Valid Range:
1 to 999

Default Value:
16
     �    Selects the corresponding channel.

Valid Range: 1 to 16     (for ENA E5070B/E5071B)
             1 to 4      (for ENA E5061A/E5062A)

Default Value: 1
   �����  �    Status                           
� %  �  �    Instrument Handle                " > � �       State                            � >� �  d    Factor                            > % �  d    Channel                            	               On VI_TRUE Off VI_FALSE    16    1    <    This function configure the smoothing for active channel.
    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (State) out of range.
BFFC0004  Parameter 4 (Smoothing Aperture) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Enables or disables the smoothing of active channel.

Valid Values:
VI_TRUE  (1) - On
VI_FALSE (0) - Off

Default Value:
VI_FALSE (0)
     s    Sets the smoothing aperture for active channel.

Valid Range:
0.05 to 25.0 percentages (%)

Default Value:
1.5 %
     �    Selects the corresponding channel.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA E5061A/E5062A)

Default Value: 1
   8����  �    Status                           � %  �  �    Instrument Handle                l > � �       State                            � >� �  d    Smoothing Aperture               w > % �  d    Channel                            	               On VI_TRUE Off VI_FALSE    1.5    1    B    This function configure absolute measurement of active channel.
    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Port) out of range.
BFFC0004  Parameter 4 (Trace) out of range.
BFFC0005  Parameter 5 (Measurement Parameter) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Selects the corresponding channel.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA E5061A/E5062A)

Default Value: 1
     �    Sets the output port for absolute measurement.

Valid Range:
Depends on the number of ports

Default Value:
1

Notes:
(1) This value is not available for ENA E5061A/E5062A.    �    Sets the measurement parameter of active channel.

Valid Values:
AGENA_MEASUREMENT_PARAMETER_S11  (0) - Specifies S11
AGENA_MEASUREMENT_PARAMETER_S21  (1) - Specifies S21
AGENA_MEASUREMENT_PARAMETER_S31  (2) - Specifies S31
AGENA_MEASUREMENT_PARAMETER_S41  (3) - Specifies S41
AGENA_MEASUREMENT_PARAMETER_S12  (4) - Specifies S12
AGENA_MEASUREMENT_PARAMETER_S22  (5) - Specifies S22
AGENA_MEASUREMENT_PARAMETER_S32  (6) - Specifies S32
AGENA_MEASUREMENT_PARAMETER_S42  (7) - Specifies S42
AGENA_MEASUREMENT_PARAMETER_S13  (8) - Specifies S13
AGENA_MEASUREMENT_PARAMETER_S23  (9) - Specifies S23
AGENA_MEASUREMENT_PARAMETER_S33 (10) - Specifies S33
AGENA_MEASUREMENT_PARAMETER_S43 (11) - Specifies S43
AGENA_MEASUREMENT_PARAMETER_S14 (12) - Specifies S14
AGENA_MEASUREMENT_PARAMETER_S24 (13) - Specifies S24
AGENA_MEASUREMENT_PARAMETER_S34 (14) - Specifies S34
AGENA_MEASUREMENT_PARAMETER_S44 (15) - Specifies S44

when the absolute measurement is executed:
AGENA_MEASUREMENT_PARAMETER_A   (16) - Specifies A
AGENA_MEASUREMENT_PARAMETER_B   (17) - Specifies B
AGENA_MEASUREMENT_PARAMETER_C   (18) - Specifies C
AGENA_MEASUREMENT_PARAMETER_D   (19) - Specifies D
AGENA_MEASUREMENT_PARAMETER_R1  (20) - Specifies R1
AGENA_MEASUREMENT_PARAMETER_R2  (21) - Specifies R2
AGENA_MEASUREMENT_PARAMETER_R3  (22) - Specifies R3
AGENA_MEASUREMENT_PARAMETER_R4  (23) - Specifies R4

Default Value:
AGENA_MEASUREMENT_PARAMETER_S11  (0)

Notes:
(1) ENA E5061A/E5062A supports only this values: S11, S21, S12, S22.
     �    Selects the corresponding trace.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA E5061A/E5062A)

Default Value: 1
   �����  �    Status                           d %  �  �    Instrument Handle                 > % �  d    Channel                          � > � �  d    Port                             Y >� � d    Measurement Parameter            #> > �  d    Trace                              	               1    1              HS11 AGENA_MEASUREMENT_PARAMETER_S11 S21 AGENA_MEASUREMENT_PARAMETER_S21 S31 AGENA_MEASUREMENT_PARAMETER_S31 S41 AGENA_MEASUREMENT_PARAMETER_S41 S12 AGENA_MEASUREMENT_PARAMETER_S12 S22 AGENA_MEASUREMENT_PARAMETER_S22 S32 AGENA_MEASUREMENT_PARAMETER_S32 S42 AGENA_MEASUREMENT_PARAMETER_S42 S13 AGENA_MEASUREMENT_PARAMETER_S13 S23 AGENA_MEASUREMENT_PARAMETER_S23 S33 AGENA_MEASUREMENT_PARAMETER_S33 S43 AGENA_MEASUREMENT_PARAMETER_S43 S14 AGENA_MEASUREMENT_PARAMETER_S14 S24 AGENA_MEASUREMENT_PARAMETER_S24 S34 AGENA_MEASUREMENT_PARAMETER_S34 S44 AGENA_MEASUREMENT_PARAMETER_S44 A AGENA_MEASUREMENT_PARAMETER_A B AGENA_MEASUREMENT_PARAMETER_B C AGENA_MEASUREMENT_PARAMETER_C D AGENA_MEASUREMENT_PARAMETER_D R1 AGENA_MEASUREMENT_PARAMETER_R1 R2 AGENA_MEASUREMENT_PARAMETER_R2 R3 AGENA_MEASUREMENT_PARAMETER_R3 R4 AGENA_MEASUREMENT_PARAMETER_R4    1    �    This function configure external signal source for selected channel.

Notes:

(1) This function is not available for ENA E5061A/E5062A.
        This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Control State) out of range.
BFFC0004  Parameter 4 (Frequency Offset State) out of range.
BFFC0005  Parameter 5 (Multiplier) out of range.
BFFC0006  Parameter 6 (Divisor) out of range.
BFFC0007  Parameter 7 (Offset) out of range.
BFFC0008  Parameter 8 (Start) out of range.
BFFC0009  Parameter 9 (Stop) out of range.
BFFC0010  Parameter 10 (Power Slope State) out of range.
BFFC0011  Parameter 11 (Power Level) out of range.
BFFC0012  Parameter 12 (Power Slope) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Selects the corresponding channel.

Valid Range: 1 to 16     (for ENA E5070B/E5071B)
             1 to 4      (for ENA E5061A/E5062A)

Default Value: 1
     �    Enables or disables the external signal source control for selected channel.

Valid Values:
VI_TRUE  (1) - Enables
VI_FALSE (0) - Disables

Default Value:
VI_FALSE (0)
    �    Sets a multiplier when making the frequency setting of the external signal source as a multiplier, divisor, or offset for selected channel.

Valid Range:
-100 to 100

Default Value:
0

Notes:
There are two methods to set the frequency range of the external signal source: using a multiplier, divisor, or offset for the normal frequency setting and using the start frequency and the stop frequency.
    �    Sets a divisor when making the frequency setting of the external signal source as a multiplier, divisor, or offset for selected channel.

Valid Range:
1 to 100

Default Value:
1

Notes:
There are two methods to set the frequency range of the external signal source: using a multiplier, divisor, or offset for the normal frequency setting and using the start frequency and the stop frequency.
    �    Sets an offset when making the frequency setting of the external signal source as a multiplier, divisor, or offset for selected channel.

Valid Range:
-1.0e+12 to 1.0e+12 Hertz (Hz)

Default Value:
0.0 Hertz (Hz)

Notes:
There are two methods to set the frequency range of the external signal source: using a multiplier, divisor, or offset for the normal frequency setting and using the start frequency and the stop frequency.
    �    Sets a start frequency when making the frequency setting of the external signal source as a start frequency and the stop frequency for selected channel.

Valid Range:
0.0 to 1.0e+12 Hertz (Hz)

Default Value:
0.0 Hertz (Hz)

Notes:
There are two methods to set the frequency range of the external signal source: using a multiplier, divisor, or offset for the normal frequency setting and using the start frequency and the stop frequency.
    �    Sets a stop frequency when making the frequency setting of the external signal source as a start frequency and the stop frequency for selected channel.

Valid Range:
0.0 to 1.0e+12 Hetz (Hz)

Default Value:
0.0 Hertz

Notes:
There are two methods to set the frequency range of the external signal source: using a multiplier, divisor, or offset for the normal frequency setting and using the start frequency and the stop frequency.
     �    Enables or disables the frequency setting of the external signal source for measurement regardless of state of the frequency offset mode for selected channel.

Valid Values:
VI_TRUE  (1) - Enables
VI_FALSE (0) - Disables

Default Value:
VI_FALSE (0)
     �    Sets the power level of the external signal source for selected channel.

Valid Range:
-150.0 to 30.0 dBm

Default Value:
-10.0 dBm
     �    Enables or disables power slope setting of the external signal source for selected channel.

Valid Values:
VI_TRUE  (1) - Enables
VI_FALSE (0) - Disables

Default Value:
VI_FALSE (0)
     �    Sets the power slope value of the external signal source for selected channel.

Valid Range:
-2.0 to 2.0 dB / GHz

Default Value:
0.0 dB / GHz
   )"����  �    Status                           /E %  �  �    Instrument Handle                /� > % �  d    Channel                          0� > � �       Control State                    18 >� �  d    Multiplier                       2� � % �  d    Divisor                          4b � � �  d    Offset                           6 � �  d    Start                            7� �� �  d    Stop                             9� >/ �       Frequency Offset State           :� � � 
�  d    Power Level                      ;" � > 	�       Power Slope State                ;� � �  d    Power Slope                        	               1  "  Enabled VI_TRUE Disabled VI_FALSE    0    1    0.0    0.0    0.0  "  Enabled VI_TRUE Disabled VI_FALSE    -10.0  "  Enabled VI_TRUE Disabled VI_FALSE    0.0    7    This function configure frequency offset parameters.
    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Port) out of range.
BFFC0004  Parameter 4 (State) out of range.
BFFC0005  Parameter 5 (Multiplier) out of range.
BFFC0006  Parameter 6 (Divisor) out of range.
BFFC0007  Parameter 7 (Offset) out of range.
BFFC0008  Parameter 8 (Start) out of range.
BFFC0009  Parameter 9 (Stop) out of range.
BFFC0010  Parameter 10 (X Axis Freq) out of range.
BFFC0011  Parameter 11 (Avoid Spurious) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Selects the corresponding channel.

Valid Range: 1 to 16     (for ENA E5070B/E5071B)
             1 to 4      (for ENA E5061A/E5062A)

Default Value: 1
     >    Selects active port.

Valid Range:
1 to 4

Default Value:
1
     �    Enables or disables the frequency setting of the external signal source for measurement regardless of state of the frequency offset mode for selected channel.

Valid Values:
VI_TRUE  (1) - Enables
VI_FALSE (0) - Disables

Default Value:
VI_FALSE (0)
    �    Sets a multiplier when the setting method for the frequency setting for the specified port is a multiplier, divisor, or offset when the frequency offset mode is on for selected channel.

Valid Range:
-100 to 100

Default Value:
1

Notes:
There are two methods to set the frequency when the frequency offset mode is on: using a multiplier, divisor, or offset for the normal frequency setting and using the start frequency and the stop frequency.
    �    Sets a divisor when the setting method for the frequency setting for the specified port is a multiplier, divisor, or offset when the frequency offset mode is on for selected channel.

Valid Range:
1 to 100

Default Value:
1

Notes:
There are two methods to set the frequency when the frequency offset mode is on: using a multiplier, divisor, or offset for the normal frequency setting and using the start frequency and the stop frequency.
    �    Sets an offset when the setting method for the frequency setting for the specified port is a multiplier, divisor, or offset when the frequency offset mode is on for selected channel.

Valid Range:
-1.0e12 to 1.0e12 Hertz (Hz)

Default Value:
0.0 Hertz (Hz)

Notes:
There are two methods to set the frequency when the frequency offset mode is on: using a multiplier, divisor, or offset for the normal frequency setting and using the start frequency and the stop frequency.
    I    Sets a start frequency when the setting method for the frequency setting for the specified port is the start frequency and the stop frequency when the frequency offset mode is on for selected channel.

Valid Range:

E5061A
300.0e+3 to 1.5e+9 Hertz (Hz)

E5062A, E5070B
300.0e+3 to 3.0e+9 Hertz (Hz)

E5071B
300.0e+3 to 8.5e+9 Hertz (Hz)

Default Value:
300.0e+3 Hertz

Notes:
There are two methods to set the frequency when the frequency offset mode is on: using a multiplier, divisor, or offset for the normal frequency setting and using the start frequency and the stop frequency.
    H    Sets a stop frequency when the setting method for the frequency setting for the specified port is the start frequency and the stop frequency when the frequency offset mode is on for selected channel.

Valid Range:

E5061A
300.0e+3 to 1.5e+9 Hertz (Hz)

E5062A, E5070B
300.0e+3 to 3.0e+9 Hertz (Hz)

E5071B
300.0e+3 to 8.5e+9 Hertz (Hz)

Default Value:
300.0e+3 Hertz

Notes:
There are two methods to set the frequency when the frequency offset mode is on: using a multiplier, divisor, or offset for the normal frequency setting and using the start frequency and the stop frequency.
    �    Sets the X-axis frequency for the active channel.

Valid Values:

For Frequency Offset State disabled
-----------------------------------
AGENA_XAXIS_FREQUENCY_NORMAL (0)
  - Normal frequency

AGENA_XAXIS_FREQUENCY_RF_PLUS_LO (1)
  - Normal frequency + frequency of the external signal source

AGENA_XAXIS_FREQUENCY_RF_MINUS_LO (2)
  - Normal frequency - frequency of the external signal source

AGENA_XAXIS_FREQUENCY_LO_MINUS_RF (3)
  - Frequency of the external signal source - normal frequency


For Frequency Offset State enabled
----------------------------------
AGENA_XAXIS_FREQUENCY_BASE (4)
  - Normal frequency

AGENA_XAXIS_FREQUENCY_STIMULUS (5)
  - Frequency for the source port for the specified measurement parameter

AGENA_XAXIS_FREQUENCY_RESPONSE (6)
  - Frequency for the receiver port for the specified measurement parameter


Default Value:
AGENA_XAXIS_FREQUENCY_NORMAL (0)

Notes:
(1) When using this function, disable the frequency offset mode.
(2) This parameter is ignored for ENA E5061A/E5062A.
    �    Enables or disables the spurious avoidance for active channel.

Valid Values:
VI_TRUE  (1) - Enabled
VI_FALSE (0) - Disabled

Default Value:
VI_FALSE (0)

Notes:
When the spurious avoidance is on, measurement is performed avoiding spurious that occurs due to the following signals.
 - Source signal and its harmonics
 - When the frequency setting for the external signal source is
   enabled, the set signal and its harmonics.
   @����  �    Status                           E� %  �  �    Instrument Handle                F� > % �  d    Channel                          G3 > � �  d    Port                             Gy >8 �       State                            H} >� �  d    Multiplier                       JD � % �  d    Divisor                          L � � �  d    Offset                           M� � �  d    Start                            P8 �� �  d    Stop                             R� � % 	� d    X Axis Freq                      V� � � 
�  `    Avoid Spurious                     	               1    1  "  Enabled VI_TRUE Disabled VI_FALSE    1    1    0.0    300.0e3    300.0e3              Normal AGENA_XAXIS_FREQUENCY_NORMAL RF + LO AGENA_XAXIS_FREQUENCY_RF_PLUS_LO RF - LO AGENA_XAXIS_FREQUENCY_RF_MINUS_LO LO - RF AGENA_XAXIS_FREQUENCY_LO_MINUS_RF Base AGENA_XAXIS_FREQUENCY_BASE Stimulus AGENA_XAXIS_FREQUENCY_STIMULUS Response AGENA_XAXIS_FREQUENCY_RESPONSE     Enable VI_TRUE Disable VI_FALSE    q    This function configure the graph layout for selected channel or the layout of the windows on the LCD display.
    [    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Graph Layout) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None    �    Sets the graph layout of selected channel.

Valid Values:
AGENA_DISPLAY_LAYOUT_D1           (0)
- Specifies the layout in which the window for channel 1 only is displayed on the entire display.

AGENA_DISPLAY_LAYOUT_D12          (1)
- Specifies the layout in which the window for channel 1 is displayed on the left side of the display area and the window for channel 2 on the right side.

AGENA_DISPLAY_LAYOUT_D1_2         (2)
- Specifies the layout in which the window for channel 1 is displayed in the upper part and the window for channel 2 in the lower part.

AGENA_DISPLAY_LAYOUT_D112         (3)
- Specifies the layout in which the window for channel 1 is displayed on the left side of 2/3 and the window for channel 2 on the right side of 1/3.

AGENA_DISPLAY_LAYOUT_D1_1_2       (4)
- Specifies the layout in which the window for channel 1 is displayed in the upper part of 2/3 and the window for channel 2 in the lower part of 1/3.

AGENA_DISPLAY_LAYOUT_D123         (5)
- Specifies the layout in which the windows for channel 1, 2, and 3 are displayed in the left side, middle part, and right side, respectively.

AGENA_DISPLAY_LAYOUT_D1_2_3       (6)
- Specifies the layout in which the windows for channel 1, 2, and 3 are displayed in the upper part, middle part, and the lower part, respectively.

AGENA_DISPLAY_LAYOUT_D12_33       (7)
- Specifies the layout in which the windows for channel 1, 2, and 3 are displayed in the upper left, upper right, and lower part, respectively.

AGENA_DISPLAY_LAYOUT_D11_23       (8)
- Specifies the layout in which the windows for channel 1, 2, and 3 are displayed in the upper part, lower left, and lower right, respectively.

AGENA_DISPLAY_LAYOUT_D13_23       (9)
- Specifies the layout in which the windows for channel 1, 2, and 3 are displayed in the upper left, lower left, and right side, respectively.

AGENA_DISPLAY_LAYOUT_D12_13       (10)
- Specifies the layout in which the windows for channel 1, 2, and 3 are displayed in the left side, upper right, and lower right, respectively.

AGENA_DISPLAY_LAYOUT_D1234        (11)
- Specifies the layout in which the windows for channel 1, 2, 3 and 4 are displayed by splitting the screen horizontally into four equal parts.

AGENA_DISPLAY_LAYOUT_D1_2_3_4     (12)
- Specifies the layout in which the windows for channel 1, 2, 3 and 4 are displayed by splitting the screen vertically into four equal parts.

AGENA_DISPLAY_LAYOUT_D12_34       (13)
- Specifies the layout in which the windows for channel 1, 2, 3, and 4 are displayed in the upper left, upper right, lower left, and lower right, respectively.

AGENA_DISPLAY_LAYOUT_D123_456     (14)
- Specifies the layout in which the windows for channel 1, 2, 3, 4, 5 and 6 are displayed in the upper left, upper middle, upper right, lower left, lower middle, and lower right, respectively.

AGENA_DISPLAY_LAYOUT_D12_34_56    (15)
- Specifies the layout in which the windows for channel 1, 2, 3, 4, 5 and 6 are displayed in the upper left, upper right, middle left, middle right, lower left, and lower right, respectively.

AGENA_DISPLAY_LAYOUT_D1234_5678   (16)
- Specifies the layout in which the windows for channel 1, 2, 3 and 4 are displayed in the upper part and the windows for channel 5, 6, 7 and 8 are displayed in the lower part of the window.

AGENA_DISPLAY_LAYOUT_D12_34_56_78 (17)
- Specifies the layout in which the windows for channel 1, 3, 5 and 7 are displayed on the left side and the windows for channel 2, 4, 6 and 8 are displayed on the right side of the window.

AGENA_DISPLAY_LAYOUT_D123_456_789 (18)
- Specifies the layout in which the windows for channel 1, 2, 3, 4, 5, 6, 7, 8 and 9 are displayed in the left, middle, and right of the upper part of the window, in the left, middle, and right of the middle part, and in the left, middle, and right of the lower part, respectively.

AGENA_DISPLAY_LAYOUT_D123__ABC    (19)
- Specifies the window layout as follows: windows for channels 1, 4, 7, and 10 from the top of the 1st column, windows for channels 2, 5, 8, and 11 from the top of the 2nd column, and windows for channels 3, 6, 9, and 12 from the top of the 3rd  column.

AGENA_DISPLAY_LAYOUT_D1234__9ABC  (20)
- Specifies the window layout as follows: windows for channels 1, 2, 3, and 4 from the left of the upper part, windows for channels 5, 6, 7, and 8 from the left of the middle part, and the windows for channels 9, 10, 11, and 12 from the left of the lower part.

AGENA_DISPLAY_LAYOUT_D1234__CDEF  (21)
- Specifies the window layout as follows: windows for channels 1, 5, 9, and 13 from the top of the 1st column, windows for channels 2, 6, 10, and 14 from the top of the 2nd column, windows for channels 3, 7, 11, and 15 from the top of the 3rd column, and windows for channels 4, 8, 12, and 16 from the top of the 4th column.

Default Value:
AGENA_DISPLAY_LAYOUT_D1 (0)

Notes:
(1) ENA E5061A/E5062A don't support this values: D123_456, D12_34_56, D1234_5678, D12_34_56_78, D123_456_789, D1234__9ABC, D123__ABC, D1234__CDEF
     �    Selects the corresponding channel for graph layout setting.

Valid Range: 0 to 16

Default Value: 1

Notes:
(1) If value = 0 then function sets the layout of windows on the LCD display.
   \�����  �    Status                           aC %  �  �    Instrument Handle                a� > � � d    Graph Layout                     u� > % �  d    Channel                            	                         +D1 AGENA_DISPLAY_LAYOUT_D1 D12 AGENA_DISPLAY_LAYOUT_D12 D1_2 AGENA_DISPLAY_LAYOUT_D1_2 D112 AGENA_DISPLAY_LAYOUT_D112 D1_1_2 AGENA_DISPLAY_LAYOUT_D1_1_2 D123 AGENA_DISPLAY_LAYOUT_D123 D1_2_3 AGENA_DISPLAY_LAYOUT_D1_2_3 D12_33 AGENA_DISPLAY_LAYOUT_D12_33 D11_23 AGENA_DISPLAY_LAYOUT_D11_23 D13_23 AGENA_DISPLAY_LAYOUT_D13_23 D12_13 AGENA_DISPLAY_LAYOUT_D12_13 D1234 AGENA_DISPLAY_LAYOUT_D1234 D1_2_3_4 AGENA_DISPLAY_LAYOUT_D1_2_3_4 D12_34 AGENA_DISPLAY_LAYOUT_D12_34 D123_456 AGENA_DISPLAY_LAYOUT_D123_456 D12_34_56 AGENA_DISPLAY_LAYOUT_D12_34_56 D1234_5678 AGENA_DISPLAY_LAYOUT_D1234_5678 D12_34_56_78 AGENA_DISPLAY_LAYOUT_D12_34_56_78 D123_456_789 AGENA_DISPLAY_LAYOUT_D123_456_789 D123_ABC AGENA_DISPLAY_LAYOUT_D123__ABC D1234_9ABC AGENA_DISPLAY_LAYOUT_D1234__9ABC D1234_CDEF AGENA_DISPLAY_LAYOUT_D1234__CDEF    1    .    This function configure display parameters.
    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Backlight) out of range.
BFFC0004  Parameter 4 (Display Update) out of range.
BFFC0005  Parameter 5 (Graticule Label) out of range.
BFFC0006  Parameter 6 (Clock) out of range.
BFFC0007  Parameter 7 (Frequency) out of range.
BFFC0008  Parameter 8 (Softkey Label) out of range.
BFFC0009  Parameter 9 (Title) out of range.
BFFC0011  Parameter 11 (Table) out of range.
BFFC0012  Parameter 12 (Table Select) out of range.
BFFC0013  Parameter 13 (Display Type) out of range.
BFFC0014  Parameter 14 (Statistic Analysis Result) out of range.
BFFC0015  Parameter 15 (Maximize) out of range.


BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Enables or disables the backlight of the LCD display.

Valid Values:
VI_TRUE  (1) - Enables
VI_FALSE (0) - Disables

Default Value:
VI_TRUE (1)

Notes:
When the backlight is disabled, you cannot read the information on the display.
     �    Enables or disables the update of the LCD display.

Valid Values:
VI_TRUE  (1) - Enables
VI_FALSE (0) - Disables

Default Value:
VI_TRUE (1)
     �    Enables or disables the display of the graticule label of selected channel.

Valid Values:
VI_TRUE  (1) - Enables
VI_FALSE (0) - Disables

Default Value:
VI_TRUE (1)
     �    Enables or disables the clock display at the right edge of the instrument status bar (at the bottom of the LCD display).

Valid Values:
VI_TRUE  (1) - Enables
VI_FALSE (0) - Disables

Default Value:
VI_TRUE (1)
    �    Turns ON/OFF the window maximization of the active channel.

Valid Values:
VI_TRUE  (1) - Enables
VI_FALSE (0) - Disables

Default Value:
VI_TRUE (1)

Notes:

(1) If channel = 0 then function maximize active channel.

(2) If you turned ON the maximization, only the window of the active channel is maximized on the LCD display and the windows of the other channels are not displayed.
     �    Enables or disables the display of the softkey labels.

Valid Values:
VI_TRUE  (1) - Enables
VI_FALSE (0) - Disables

Default Value:
VI_TRUE (1)
     �    Enables or disables the display of the title label of selected channel in the title area.

Valid Values:
VI_TRUE  (1) - Enables
VI_FALSE (0) - Disables

Default Value:
VI_FALSE (0)
     �    Sets the title label displayed in the title area of selected channel.

Default Value:
""

Notes:
This control is valid only if Title is enabled.     �    Selects the corresponding channel for display configuration.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA E5061A/E5062A)

Default Value: 1
     �    Enables or disables the display of the window selected with in Table Type control.

Valid Values:
VI_TRUE  (1) - Enables
VI_FALSE (0) - Disables

Default Value:
VI_FALSE (0)
         Selects the window whose display is enabled or disabled with the Table control.

Valid Values:
AGENA_DISPLAY_TABLE_TYPE_MARKER   (0) - Marker table
AGENA_DISPLAY_TABLE_TYPE_LIMIT    (1) - Limit test table
AGENA_DISPLAY_TABLE_TYPE_SEGMENT  (2) - Segment table
AGENA_DISPLAY_TABLE_TYPE_ECHO     (3) - Echo window
AGENA_DISPLAY_TABLE_TYPE_PLOSS    (4) - loss compensation table
AGENA_DISPLAY_TABLE_TYPE_SCFACTOR (5) - power sensor's callibration factor table

Default Value:
AGENA_DISPLAY_TABLE_TYPE_MARKER   (0)
    O    Selects the display type of the LCD display.

Valid Values:
AGENA_DISPLAY_TYPE_NORMAL (0)
  - Specifies the normal display (background color: black).

AGENA_DISPLAY_TYPE_INVERT (1)
  - Specifies the display in which the color of the normal display is inverted (background color: white).

Default Value:
AGENA_DISPLAY_TYPE_NORMAL (0)
    %    For the active trace of selected channel, enables or disables the statistics value display (the mean vale, the standard deviation, and the difference between the maximum value and the minimum value).

Valid Values:
VI_TRUE  (1) - Enables
VI_FALSE (0) - Disables

Default Value:
VI_FALSE (0)
     �    Enables or disables the frequency display on the LCD display.

Valid Values:
VI_TRUE  (1) - Enables
VI_FALSE (0) - Disables

Default Value:
VI_TRUE (1)
   z�����  �    Status                           �, %  �  �    Instrument Handle                �� % � �       Backlight                        �� % � �       Display Update                   �T %? �       Graticule Label                  � %� �       Clock                            �� �j �       Maximize                         �k c  �       Softkey Label                    � c i �       Title                            �� c � 	�  �    Title Text                       �_ %  �  d    Channel                          � cj 
�       Table                            �� c� � d    Table Select                     �� �  � d    Display Type                     �0 � � �       Statistic Analysis Result        �] %� �       Frequency                          	               Enable VI_TRUE Disable VI_FALSE    Enable VI_TRUE Disable VI_FALSE    Enable VI_TRUE Disable VI_FALSE    Enable VI_TRUE Disable VI_FALSE    Enable VI_TRUE Disable VI_FALSE    Enable VI_TRUE Disable VI_FALSE     Enable VI_TRUE Disable VI_FALSE    ""    1     Enable VI_TRUE Disable VI_FALSE               �Marker AGENA_DISPLAY_TABLE_TYPE_MARKER Limit AGENA_DISPLAY_TABLE_TYPE_LIMIT Segment AGENA_DISPLAY_TABLE_TYPE_SEGMENT Echo AGENA_DISPLAY_TABLE_TYPE_ECHO Ploss AGENA_DISPLAY_TABLE_TYPE_PLOSS SC Factor AGENA_DISPLAY_TABLE_TYPE_SCFACTOR               BNormal AGENA_DISPLAY_TYPE_NORMAL Invert AGENA_DISPLAY_TYPE_INVERT     Enable VI_TRUE Disable VI_FALSE    Enable VI_TRUE Disable VI_FALSE    3    This function configure display of active trace.
    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Trace) out of range.
BFFC0004  Parameter 4 (Trace Display) out of range.
BFFC0005  Parameter 5 (Display Data) out of range.
BFFC0006  Parameter 6 (Display Memory) out of range.


BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Selects the corresponding channel for configuration.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA E5061A/E5062A)

Default Value: 1
    �    For the active trace of selected channel, selects the data trace display method (math method between measurement data and memory trace data).

Valid Values:
AGENA_DISPLAY_TRACE_NORMAL   (0) - Normal Data
AGENA_DISPLAY_TRACE_ADD      (1) - Data + Memory
AGENA_DISPLAY_TRACE_SUBTRACT (2) - Data - Memory
AGENA_DISPLAY_TRACE_MULTIPLY (3) - Data * Memory
AGENA_DISPLAY_TRACE_DIVIDE   (4) - Data / Memory

Default Value:
AGENA_DISPLAY_TRACE_NORMAL   (0)
     �    Selects the corresponding trace for configuration.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA E5061A/E5062A)

Default Value: 1
     �    Enables or disables the display of the data trace for selected trace of selected channel.

Valid Values:
VI_TRUE  (1) - Enables
VI_FALSE (0) - Disables

Default Value:
VI_TRUE (1)
     �    Enables or disables the display of the memory trace for selected trace of selected channel.

Valid Values:
VI_TRUE  (1) - Enables
VI_FALSE (0) - Disables

Default Value:
VI_TRUE (1)
   �L����  �    Status                           �E %  �  �    Instrument Handle                �� > % �  d    Channel                          �� >� � d    Trace Display                    �a > � �  d    Trace                            � � ( �       Display Data                     �� � � �       Display Memory                     	               1               �Normal AGENA_DISPLAY_TRACE_NORMAL Add AGENA_DISPLAY_TRACE_ADD Subtract AGENA_DISPLAY_TRACE_SUBTRACT Multiply AGENA_DISPLAY_TRACE_MULTIPLY Divide AGENA_DISPLAY_TRACE_DIVIDE    1    Enable VI_TRUE Disable VI_FALSE    Enable VI_TRUE Disable VI_FALSE    5    This function sets color of specific display item.
    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Display Type) out of range.
BFFC0003  Parameter 3 (Trace) out of range.
BFFC0004  Parameter 4 (Setting) out of range.
BFFC0005  Parameter 5 (R) out of range.
BFFC0006  Parameter 6 (G) out of range.
BFFC0007  Parameter 7 (B) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None    S    Selects display color setting.

Valid Values:
AGENA_DISPLAY_COLOR_DATA_TRACE        (0)
  - Data trace

AGENA_DISPLAY_COLOR_MEMORY_TRACE      (1)
  - Memory trace

AGENA_DISPLAY_COLOR_GRAPH_OUTER_FRAME (2)
  - Outer frame line of the graph

AGENA_DISPLAY_COLOR_GRAPH_GRID_LINE   (3)
  - Grid line of the graph

AGENA_DISPLAY_COLOR_LIMIT_TEST_RESULT (4)
  - Fail display color used for the limit test result

AGENA_DISPLAY_COLOR_LIMIT_LINE        (5)
  - Color of the limit line

AGENA_DISPLAY_COLOR_BACKGROUND        (6)
  - Background color

Default Value:
AGENA_DISPLAY_COLOR_DATA_TRACE (0)
     A    Sets red part of color.

Valid Range:
0 to 5

Default Value:
0
     B    Sets green part of color.

Valid Range:
0 to 5

Default Value:
0     A    Sets blue part of color.

Valid Range:
0 to 5

Default Value:
0    O    Selects the display type of the LCD display.

Valid Values:
AGENA_DISPLAY_TYPE_NORMAL (0)
  - Specifies the normal display (background color: black).

AGENA_DISPLAY_TYPE_INVERT (1)
  - Specifies the display in which the color of the normal display is inverted (background color: white).

Default Value:
AGENA_DISPLAY_TYPE_NORMAL (0)
     c    Selects the corresponding trace for color configuration.

Valid Range: 1 to 16

Default Value: 1
   �Z����  �    Status                           �a %  �  �    Instrument Handle                �  >� � d    Setting                          �[ � % �  d    R                                �� � � �  d    G                                �� �� �  d    B                                �7 > % � d    Display Type                     �� > � �  d    Trace                              	                         PData Trace AGENA_DISPLAY_COLOR_DATA_TRACE Memory Trace AGENA_DISPLAY_COLOR_MEMORY_TRACE Graph Outer Frame AGENA_DISPLAY_COLOR_GRAPH_OUTER_FRAME Graph Grid Line AGENA_DISPLAY_COLOR_GRAPH_GRID_LINE Limit Test Result AGENA_DISPLAY_COLOR_LIMIT_TEST_RESULT Limit Line AGENA_DISPLAY_COLOR_LIMIT_LINE Background AGENA_DISPLAY_COLOR_BACKGROUND    0    0    0               BNormal AGENA_DISPLAY_TYPE_NORMAL Invert AGENA_DISPLAY_TYPE_INVERT    1    o    This function selects the display method of the graph horizontal axis of selected channel for segment sweep.
    ]    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Display Method) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None    �    Selects the display method of the graph horizontal axis of selected channel for segment sweep.

Valid Values:
AGENA_DISPLAY_XAXIS_LINEAR     (0)
  - Specifies the frequency base (linear frequency axis with the
minimum frequency at the left edge and the maximum frequency at the right edge).

AGENA_DISPLAY_XAXIS_ORDER_BASE (1)
  - Specifies the order base (axis in which the measurement point numbers are positioned evenly in the order of measurement).

Default Value:
AGENA_DISPLAY_XAXIS_LINEAR (0)
     t    Selects the corresponding channel for X-axis segment sweep configuration.

Valid Range: 1 to 16

Default Value: 1
   ������  �    Status                           �Q %  �  �    Instrument Handle                �� > � � d    Display Method                   �� > % �  d    Channel                            	                          LLinear AGENA_DISPLAY_XAXIS_LINEAR Order Base AGENA_DISPLAY_XAXIS_ORDER_BASE    1    /    This function configure display corrections.
    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Electrical Delay Time) out of range.
BFFC0004  Parameter 4 (Velocity Factor) out of range.
BFFC0005  Parameter 5 (Phase Offset) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Sets the electrical delay time of the active trace of selected channel.

Valid Range:
-10.0 to 10.0 seconds

Default Value:
0.0 seconds
     `    For selected channel, sets the velocity factor.

Valid Range:
0.0 to 10.0

Default Value:
1.0
     s    Sets the phase offset of the active trace of selected channel.

Valid Range:
-360.0 to 360.0

Default Value:
0.0
     �    Selects the corresponding channel for corrections configuration.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA E5061A/E5062A)

Default Value: 1
   ������  �    Status                           �� %  �  �    Instrument Handle                �Y > � �  d    Electrical Delay Time            �� >� �  d    Velocity Factor                  �S � % �  d    Phase Offset                     �� > % �  d    Channel                            	               0.0    1.0    0.0    1    )    This function configure display scale.
    A    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Trace) out of range.
BFFC0004  Parameter 4 (Number of Divisions) out of range.
BFFC0005  Parameter 5 (Scale per Division) out of range.
BFFC0006  Parameter 6 (Reference Graticule Line) out of range.
BFFC0007  Parameter 7 (Value Graticule Line) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     K    Selects the corresponding trace.

Valid Range: 1 to 16

Default Value: 1
     �    Sets the number of divisions of all the graphs of selected channel.
The number of graticule line depends on this setting.

Valid Range:
4 to 30

Default value:
10
     e    Selects the corresponding channel for scale configuration.

Valid Range: 1 to 16

Default Value: 1
     �    For selected trace of selected channel, sets the value of the reference graticule line.

Valid Range:
-5.0e8 to 5.0e8

Default Value:
0.0
     �    For selected trace 1 of selected channel, specifies a reference graticule line with its number (an integer assigned starting from 0 from the lowest division).

Valid Range:
0 to the number of divisions

Default Value:
5
    G    For selected trace of selected channel: when the data format is not the Smith chart format or the polar format, sets the scale per division; when the data format is the Smith chart format or the polar format, sets the full scale value (the value of the outermost circle).

Valid Range:
1.0e-18 to 1.0e18

Default Value:
10.0
   �%����  �    Status                           �n %  �  �    Instrument Handle                � > � �  d    Trace                            �` >} �  d    Number of Divisions              � > % �  d    Channel                          �z �} �  d    Value Graticule Line             � � � �  d    Reference Graticule Line         �� � % �  d    Scale per Division                 	               1    10    1    0.0    5    10.0    2    This function configure calibration parameters.
    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Cal Kit) out of range.
BFFC0004  Parameter 4 (Cal Type) out of range.
BFFC0005  Parameter 5 (Port 1) out of range.
BFFC0006  Parameter 6 (Port 2) out of range.
BFFC0007  Parameter 7 (Port 3) out of range.
BFFC0008  Parameter 8 (Error Correction State) out of range.
BFFC0009  Parameter 9 (Calibration Property Display) out of range.
BFFC0010  Parameter 10 (Velocity Factor) out of range.
BFFC0011  Parameter 11 (Z0) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     [    Selects the calibration kit of selected channel.

Valid Range:
1 to 10

Default Value:
1
     �    Selects the corresponding channel for configure calibration.

Valid Range: 1 to 16     (for ENA E5070B/E5071B)
             1 to 4      (for ENA E5061A/E5062A)

Default Value: 1
    �    Selects the calibration type.

Valid Values:
AGENA_CALIBRATION_TYPE_OPEN    (0)
  - Response calibration (open).

AGENA_CALIBRATION_TYPE_SHORT   (1)
  - Response calibration (short).

AGENA_CALIBRATION_TYPE_THROUGH (2)
  - Response calibration (thru) between the 2 specified ports.

AGENA_CALIBRATION_TYPE_1_PORT  (3)
  - 1-port calibration of the specified port.

AGENA_CALIBRATION_TYPE_2_PORT  (4)
  - Full 2-port calibration between the 2 specified ports.

AGENA_CALIBRATION_TYPE_3_PORT  (5)
  - Full 3-port calibration between the 3 specified ports.

AGENA_CALIBRATION_TYPE_4_PORT  (6)
  - Full 4-port calibration.

AGENA_CALIBRATION_TYPE_EN_RESPONSE  (7)
  - Enhaced response calibration.

Default Value:
AGENA_CALIBRATION_TYPE_4_PORT (6)

Notes:

(1) ENA E5061A/E5062A don't support this values: AGENA_CALIBRATION_TYPE_3_PORT, AGENA_CALIBRATION_TYPE_4_PORT

(2) Enhanced response is available only for ENA E5061A/E5062A.
     �    Sets port number for calibration.

Valid Range:
1 to 4

Default Value:
1

Notes:
For full 4-port calibration value is not used.     �    Sets port number for calibration.

Valid Range:
1 to 4

Default Value:
1

Notes:
For open, short, 1-port and full 4-port calibration value is not used.     �    Sets port number for calibration.

Valid Range:
1 to 4

Default Value:
1

Notes:
For open, short, 1-port, full 3-port and full 4-port calibration value is not used.     �    Enables or disables the error correction for selected channel.

Valid Values:
VI_TRUE  (1) - Enable
VI_FALSE (0) - Disable

Default Value:
VI_FALSE (0)
     �    Enables or disables the display of the calibration property of selected channel.

Valid Values:
VI_TRUE  (1) - Enable
VI_FALSE (0) - Disable

Default Value:
VI_FALSE (0)
     `    For selected channel, sets the velocity factor.

Valid Range:
0.0 to 10.0

Default Value:
1.0
     �    Sets the system characteristic impedance (Z0) value.

Valid Range:
1.0e-3 to 1000.0 Ohms

Default Value:
50.0 Ohms

Notes:
(1) This control is available with the firmware version 3.01 or greater.

(2) This control is ignored for ENA E5061A/E5062A.
   �Y����  �    Status                           �N %  �  �    Instrument Handle                �� > � �  d    Cal Kit                          �P > % �  d    Channel                          � >� � d    Cal Type                         ڵ p % �  d    Port 1                           �> p � �  d    Port 2                           �� p� �  d    Port 3                           ܍ � > �       Error Correction State           �/ � � �       Calibration Property Display     �� �� 	�  d    Velocity Factor                  �K � % 
�  d    Z0                                 	               1    1             COpen AGENA_CALIBRATION_TYPE_OPEN Short AGENA_CALIBRATION_TYPE_SHORT Through AGENA_CALIBRATION_TYPE_THROUGH 1-port AGENA_CALIBRATION_TYPE_1_PORT Full 2-port AGENA_CALIBRATION_TYPE_2_PORT Full 3-port AGENA_CALIBRATION_TYPE_3_PORT Full 4-port AGENA_CALIBRATION_TYPE_4_PORT Enhanced Response AGENA_CALIBRATION_TYPE_EN_RESPONSE    1    1    1     Enable VI_TRUE Disable VI_FALSE     Enable VI_TRUE Disable VI_FALSE    1.0    50.0    4    This function configure calibration kit standard.
        This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Standard) out of range.
BFFC0005  Parameter 5 (Type) out of range.
BFFC0006  Parameter 6 (C0) out of range.
BFFC0007  Parameter 7 (C1) out of range.
BFFC0008  Parameter 8 (C2) out of range.
BFFC0009  Parameter 9 (C3) out of range.
BFFC0010  Parameter 10 (L0) out of range.
BFFC0011  Parameter 11 (L1) out of range.
BFFC0012  Parameter 12 (L2) out of range.
BFFC0013  Parameter 13 (L3) out of range.
BFFC0014  Parameter 14 (Arbitrary Impedance) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     R    Sets the name of the selected standard for selected channel.

Default Value:
""
     �    Selects the corresponding channel for calibration kit standard.

Valid Range: 1 to 16     (for ENA E5070B/E5071B)
             1 to 4      (for ENA E5061A/E5062A)

Default Value: 1
     �    Selects active standard for setting.

Valid Range:
1 to 21    (for ENA E5070B/E5071B)
1 to 4     (for ENA E5061A/E5062A)

Default Value:
1
    �    For the calibration kit selected for active channel, sets the
standard type of the selected standard1.

Valid Values:
AGENA_CALIB_STANDARD_OPEN  (0) - Open
AGENA_CALIB_STANDARD_SHORT (1) - Short
AGENA_CALIB_STANDARD_LOAD  (2) - Load
AGENA_CALIB_STANDARD_THRU  (3) - Thru
AGENA_CALIB_STANDARD_ARBI  (4) - Arbitrary impedance
AGENA_CALIB_STANDARD_NONE  (5) - DUT of which theoretical values are 0

Default Value:
AGENA_CALIB_STANDARD_OPEN  (0)
     �    For the calibration kit selected for active channel, sets the
value of the C0 of the selected standard.

Valid Range:
-1.0e18 to 1.0e18

Default Value:
0.0

Units:
fentofarad (fF)     �    For the calibration kit selected for active channel, sets the
value of the C1 of the selected standard.

Valid Range:
-1.0e18 to 1.0e18

Default Value:
0.0

Units:
1.0e-27 farad/hertz (F/Hz)     �    For the calibration kit selected for active channel, sets the
value of the C2 of the selected standard.

Valid Range:
-1.0e18 to 1.0e18

Default Value:
0.0

Units:
1.0e-36 farad/hertz^2 (F/Hz^2)
     �    For the calibration kit selected for active channel, sets the value of the C3 of the selected standard.

Valid Range:
-1.0e18 to 1.0e18

Default Value:
0.0

Units:
1.0e-45 farad/hertz^3 (F/Hz^3)     �    For the calibration kit selected for active channel, sets the value of the L0 of the selected standard.

Valid Range:
-1.0e18 to 1.0e18

Default Value:
0.0

Units:
picohenry (pH)     �    For the calibration kit selected for active channel, sets the value of the L1 of the selected standard.

Valid Range:
-1.0e18 to 1.0e18

Default Value:
0.0

Units:
1.0e-24 henry/hertz (H/Hz)     �    For the calibration kit selected for active channel, sets the
value of the L2 of the selected standard.

Valid Range:
-1.0e18 to 1.0e18

Default Value:
0.0

Units:
1.0e-33 henry/hertz^2 (H/Hz^2)     �    For the calibration kit selected for active channel, sets the value of the L3 of the selected standard.

Valid Range:
-1.0e18 to 1.0e18

Default Value:
0.0

Units:
1.0e-42 henry/hertz^3 (H/Hz^3)     �    For the calibration kit selected for active channel, sets the value of the arbitrary impedance of the selected standard.

Valid Range:
-1.0e18 to 1.0e18 ohms

Default Value:
0.0 ohms
     h    Sets a calibration kit name for the calibration kit selected for selected channel.

Default Value:
""
   ������  �    Status                           �� %  �  �    Instrument Handle                � > �  d    Label                            �� > % �  d    Channel                          � > � �  d    Standard                         �2 >� � d    Type                             �� p % �  d    C0                               � p � �  d    C1                               �{ p �  d    C2                               �H p� �  d    C3                               � � % 	�  d    L0                               �� � � 
�  d    L1                               � � �  d    L2                               �d �� �  d    L3                               �0 � % �  d    Arbitrary Impedance              �� � � �  d    Cal Kit Name                       	               ""    1    1               �Open AGENA_CALIB_STANDARD_OPEN Short AGENA_CALIB_STANDARD_SHORT Load AGENA_CALIB_STANDARD_LOAD Thru AGENA_CALIB_STANDARD_THRU Arbitrary impedance AGENA_CALIB_STANDARD_ARBI None AGENA_CALIB_STANDARD_NONE    0.0    0.0    0.0    0.0    0.0    0.0    0.0    0.0    0.0    ""    ;    This function configure calibration kit standard offset.
    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Standard) out of range.
BFFC0004  Parameter 4 (Offset Delay) out of range.
BFFC0005  Parameter 5 (Offset Loss) out of range.
BFFC0006  Parameter 6 (Z0) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Selects the corresponding channel for calibration kit standard offset.

Valid Range: 1 to 16     (for ENA E5070B/E5071B)
             1 to 4      (for ENA E5061A/E5062A)

Default Value: 1
     �    Selects active standard for setting.

Valid Range:
1 to 21    (for ENA E5070B/E5071B)
1 to 4     (for ENA E5061A/E5062A)

Default Value:
1
     �    For the calibration kit selected for active channel, sets the value of the offset delay of the selected standard.

Valid Range:
-1.0e18 to 1.0e18 seconds (s)

Default Value:
0.0 seconds (s)     �    For the calibration kit selected for active channel, sets the value of the offset loss of the selected standard.

Valid Range:
-1.0e18 to 1.0e18 ohm/second

Default Value:
0.0 ohm/second     �    For the calibration kit selected for active channel, sets the value of the Offset Z0 of the selected standard.

Valid Range:
-1.0e18 to 1.0e18 ohm

Default Value:
0.0 ohm   �3����  �    Status                           � %  �  �    Instrument Handle                �� > % �  d    Channel                           � > � �  d    Standard                          > �  d    Offset Delay                     � >� �  d    Offset Loss                      � p % �  d    Z0                                 	               1    1    0.0    0.0    0.0    1    This function configure calibration kit class.
    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Type) out of range.
BFFC0004  Parameter 4 (Standard) out of range.
BFFC0005  Parameter 5 (Port 1) out of range.
BFFC0006  Parameter 6 (Port 2) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Selects the corresponding channel for calibration class.

Valid Range: 1 to 16     (for ENA E5070B/E5071B)
             1 to 4      (for ENA E5061A/E5062A)

Default Value: 1
     K    Sets port number for calibration.

Valid Range:
1 to 4

Default Value:
1
     �    Sets port number for calibration.

Valid Range:
1 to 4

Default Value:
1

Notes:
Valid only for AGENA_CALIB_STANDARD_THRU type.
    ?    For the calibration kit selected for active channel, sets the
standard type of the selected standard.

Valid Values:
AGENA_CALIB_STANDARD_OPEN  (0) - Open
AGENA_CALIB_STANDARD_SHORT (1) - Short
AGENA_CALIB_STANDARD_LOAD  (2) - Load
AGENA_CALIB_STANDARD_THRU  (3) - Thru

Default Value:
AGENA_CALIB_STANDARD_OPEN  (0)
     O    Selects active standard for setting.

Valid Range:
1 to 21

Default Value:
1
   3����  �    Status                           
 %  �  �    Instrument Handle                
� > % �  d    Channel                          m p % �  d    Port 1                           � p � �  d    Port 2                           J > � � d    Type                             � >� �  d    Standard                           	               1    1    1               ~Open AGENA_CALIB_STANDARD_OPEN Short AGENA_CALIB_STANDARD_SHORT Load AGENA_CALIB_STANDARD_LOAD Thru AGENA_CALIB_STANDARD_THRU    1    3    This function configure port extension settings.
    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (State) out of range.
BFFC0004  Parameter 4 (Port 1) out of range.
BFFC0005  Parameter 5 (Correction Value) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Selects the corresponding channel for port extension configuration.

Valid Range: 1 to 16     (for ENA E5070B/E5071B)
             1 to 4      (for ENA E5061A/E5062A)

Default Value: 1
     �    For selected channel, sets the correction amount for the port extension of selected port as the delay time.

Valid Range:
-10.0 to 10.0 seconds (s)

Default Value:
0.0 seconds (s)
     �    Enables or disables the port extension for selected channel.

Valid Values:
VI_TRUE  (1) - Enable
VI_FALSE (0) - Disable

Default Value:
VI_FALSE (0)
     �    Sets port number for port extension setting.

Valid Range:
1 to 4     (for ENA E5070B/E5071B)
1 to 2     (for ENA E5061A/E5062A)

Default Value:
1
   G����  �    Status                            %  �  �    Instrument Handle                � > % �  d    Channel                          i � % �  d    Correction Value                 ' > � �       State                            � >� �  d    Port 1                             	               1    0.0     Enable VI_TRUE Disable VI_FALSE    1    �    This function configure electrical calibration.

Notes:
This function is available with the firmware version 3.50 or greater.
    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Isolation Measurement) out of range.
BFFC0004  Parameter 4 (Characterization) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Selects the corresponding channel for electrical calibration.

Valid Range: 1 to 16     (for ENA E5070B/E5071B)
             1 to 4      (for ENA E5061A/E5062A)

Default Value: 1
     �    For selected channel, enables or disables the isolation measurement when executing Ecal (Electrical Calibration).

Valid Values:
VI_TRUE  (1) - Enable
VI_FALSE (0) - Disable

Default Value:
VI_FALSE (0)
    J    For selected channel, selects the ECal characteristic used when executing the user-defined ECal.
The user-defined ECal is a type of ECal that is executed using the characteristic stored in the ECal's flash memory that has been acquired by the user. For more information, refer to User's Guide.
When the ECal module is not connected or the characteristic is not stored at the specified location number, executing this command will cause an error and the execution will be ignored.

Valid Values:
AGENA_ECAL_CHARACTERIZATION_CHAR0 (0)
  - Specifies the factory-default characteristic. (Normal ECal).

AGENA_ECAL_CHARACTERIZATION_CHAR1 (1)
  - Specifies the characteristic stored at location number 1 in the ECal's flash memory.

AGENA_ECAL_CHARACTERIZATION_CHAR2 (2)
  - Specifies the characteristic stored at location number 2 in the ECal's flash memory.

AGENA_ECAL_CHARACTERIZATION_CHAR3 (3)
  - Specifies the characteristic stored at location number 3 in the ECal's flash memory.

AGENA_ECAL_CHARACTERIZATION_CHAR4 (4)
  - Specifies the characteristic stored at location number 4 in the ECal's flash memory.

AGENA_ECAL_CHARACTERIZATION_CHAR5 (5)
  - Specifies the characteristic stored at location number 5 in the ECal's flash memory.

Default Value:
AGENA_ECAL_CHARACTERIZATION_CHAR0 (0)

Notes:
(1) This control is ignored for ENA E5061A/E5062A.

   n����  �    Status                            %  �  �    Instrument Handle                � > % �  d    Channel                           m > � �       Isolation Measurement            !B >� � d    Characterization                   	               1     Enable VI_TRUE Disable VI_FALSE               �Char 0 AGENA_ECAL_CHARACTERIZATION_CHAR0 Char 1 AGENA_ECAL_CHARACTERIZATION_CHAR1 Char 2 AGENA_ECAL_CHARACTERIZATION_CHAR2 Char 3 AGENA_ECAL_CHARACTERIZATION_CHAR3 Char 4 AGENA_ECAL_CHARACTERIZATION_CHAR4 Char 5 AGENA_ECAL_CHARACTERIZATION_CHAR5    x    This function configure power calibration settings.

Notes:

(1) This function is not available for ENA E5061A/E5062A.    (    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Port) out of range.
BFFC0004  Parameter 4 (State) out of range.
BFFC0005  Parameter 5 (Averaging Factor) out of range.
BFFC0006  Parameter 6 (Loss Compensation) out of range.
BFFC0007  Parameter 7 (Power Meter Address) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     c    Selects the corresponding channel for power calibration.

Valid Range: 1 to 16

Default Value: 1
     �    For selected port of selected channel, enables or disables the error correction of the power level.

Valid Values:
VI_TRUE  (1) - Enable
VI_FALSE (0) - Disable

Default Value:
VI_FALSE (0)
     �    For selected port of selected channel, sets the number of power calibration data measurements per measurement point (averaging factor).

Valid Range:
1 to 100

Default Value:
1
     Q    Sets port number for power calibration.

Valid Range:
1 to 4

Default Value:
1
     �    For selected port of selected channel, enables or disables the loss compensation.

Valid Values:
VI_TRUE  (1) - Enable
VI_FALSE (0) - Disable

Default Value:
VI_FALSE (0)
     _    Sets out the GPIB address of the power meter in use.

Valid Range:
0 to 30

Default Value:
1
   )Z����  �    Status                           .� %  �  �    Instrument Handle                /) > % �  d    Channel                          /� >� �       State                            0[ � % �  d    Averaging Factor                 1 > � �  d    Port                             1o � � �       Loss Compensation                2$ �� �  d    Power Meter Address                	               1     Enable VI_TRUE Disable VI_FALSE    1    1     Enable VI_TRUE Disable VI_FALSE    1    �    This function sets the reference calibration factor (the calibration factor at 50 MHz) for selected power sensor.

Notes:

(1) This function is not available for ENA E5061A/E5062A.
    p    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Power Sensor) out of range.
BFFC0003  Parameter 3 (Reference Calibration Factor) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Sets the reference calibration factor (the calibration factor at 50 MHz) for selected power sensor.

Valid Range:
1.0 to 150.0 percent (%)

Default Value:
100.0 percent (%)
    �    For selected port of selected channel, measure the power calibration data using the specified power sensor. When the measurement is complete successfully, the power level error correction is automatically turned on.
If the power sensor is not connected, an error occurs and the command is ignored.

Valid Values:
AGENA_POWER_CALIBRATION_SENSOR_A (0) - Power sensor A
AGENA_POWER_CALIBRATION_SENSOR_B (1) - Power sensor B

Default Value:
AGENA_POWER_CALIBRATION_SENSOR_A (0)
   5\����  �    Status                           9� %  �  �    Instrument Handle                :s > � �  d    Reference Calibration Factor     ;* > % � d    Power Sensor                       	               100.0               TSensor A AGENA_POWER_CALIBRATION_SENSOR_A Sensor B AGENA_POWER_CALIBRATION_SENSOR_B    �    This function sets the calibration factor table for selected power sensor.

Notes:

(1) This function is not available for ENA E5061A/E5062A.
    ^    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Power Sensor) out of range.
BFFC0003  Parameter 3 (Array Size) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     k    Sets the frequency for selected power sensor.

Valid Range for each element:
1.0e3 to 500.0e9 hertz (Hz)
     f    Specifies size of calibration factor and frequency array.

Valid Range:
0 to 100

Default Value:
0

    �    For selected port of selected channel, measure the power calibration data using the specified power sensor. When the measurement is complete successfully, the power level error correction is automatically turned on.
If the power sensor is not connected, an error occurs and the command is ignored.

Valid Values:
AGENA_POWER_CALIBRATION_SENSOR_A (0) - Power sensor A
AGENA_POWER_CALIBRATION_SENSOR_B (1) - Power sensor B

Default Value:
AGENA_POWER_CALIBRATION_SENSOR_A (0)
     q    Sets the calibration factor for selected power sensor.

Valid Range for each element:
1.0 to 100.0 percent (%)
   >�����  �    Status                           C\ %  �  �    Instrument Handle                C� >� �  d    Frequency Array                  Dn > � �  d    Array Size                       D� > % � d    Power Sensor                     F� � % �  d    Calibration Factor Array           	                   0               TSensor A AGENA_POWER_CALIBRATION_SENSOR_A Sensor B AGENA_POWER_CALIBRATION_SENSOR_B        �    This function sets the loss compensation table for selected port of selected channel.

Notes:

(1) This function is not available for ENA E5061A/E5062A.    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Port) out of range.
BFFC0004  Parameter 4 (Array Size) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     i    Selects the corresponding channel for loss compensation table.

Valid Range: 1 to 16

Default Value: 1
     W    Sets port number for loss compensation table.

Valid Range:
1 to 4

Default Value:
1
     d    Specifies size of loss compensation and frequency array.

Valid Range:
0 to 100

Default Value:
0
     w    Sets the frequency for selected port of selected channel.

Valid Range for each element:
1.0e3 to 500.0e9 hertz (Hz)
     v    Sets the loss compensation for selected port of selected channel.

Valid Range for each element:
-100.0 to 100.0 dB
   I�����  �    Status                           N% %  �  �    Instrument Handle                N� > % �  d    Channel                          O5 > � �  d    Port                             O� >� �  d    Array Size                       P  � % �  d    Frequency Array                  P � � �  d    Loss Compensation Array            	               1    1    0            x    This function configure scalar-mixer calibration.

Notes:

(1) This function is not available for ENA E5061A/E5062A.

    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Method) out of range.
BFFC0004  Parameter 4 (Port 1) out of range.
BFFC0005  Parameter 5 (Port 2) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     j    Selects the corresponding channel for scalar-mixer calibration.

Valid Range: 1 to 16

Default Value: 1
     K    Sets port number for calibration.

Valid Range:
1 to 4

Default Value:
1
     �    Sets port number for calibration.

Valid Range:
1 to 4

Default Value:
1

Notes:
Valid only for 2-port scalar-mixer calibration.     �    Selects calibration method.

Valid Values:
AGENA_SCALAR_MIXER_CALIB_1_PORT (0)
  - 1-port scalar-mixer calibration

AGENA_SCALAR_MIXER_CALIB_2_PORT (1)
  - Scalar-Mixer Calibration

Default Value:
AGENA_SCALAR_MIXER_CALIB_1_PORT (0)
   S����  �    Status                           W� %  �  �    Instrument Handle                Xm > % �  d    Channel                          X� >� �  d    Port 1                           Y2 � % �  d    Port 2                           Y� > � � �    Method                             	               1    1    1               lScalar-Mixer Calibration AGENA_SCALAR_MIXER_CALIB_2_PORT 1-port Calibration AGENA_SCALAR_MIXER_CALIB_1_PORT    |    This function enables or disables receiver correction.

Notes:

(1) This function is not available for ENA E5061A/E5062A.
    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Receiver) out of range.
BFFC0004  Parameter 4 (State) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     f    Selects the corresponding channel for receiver calibration.

Valid Range: 1 to 16

Default Value: 1
     f    Selects the corresponding receiver for receiver calibration.

Valid Range: 1 to 4

Default Value: 1
     �    For selected receiver of selected channel, enables or disables the receiver correction.

Valid Values:
VI_TRUE  (1) - Enable
VI_FALSE (0) - Disable

Default Value:
VI_FALSE (0)
   ]����  �    Status                           a� %  �  �    Instrument Handle                b5 > % �  d    Channel                          b� > � �  d    Receiver                         c >� �       State                              	               1    1     Enable VI_TRUE Disable VI_FALSE    #    This function configure trigger.
    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Continuous Sweep) out of range.
BFFC0004  Parameter 4 (Point Trigger) out of range.
BFFC0005  Parameter 5 (Trigger Source) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Enables or disables the continuous initiation mode of selected channel in the trigger system.

Valid Values:
VI_TRUE  (1) - Enable
VI_FALSE (0) - Disable

Default Value:
VI_TRUE (1)
     �    Selects the corresponding channel for trigger configuration.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA D5061A/E5062A)

Default Value: 1
    v    Enables or disables the point trigger feature.
The sweep mode is changed to "Stepped" when the point trigger feature is turned on.

Valid Values:
VI_TRUE  (1) - Enable
VI_FALSE (0) - Disable

Default Value:
VI_FALSE (0)

Notes:
(1) When the trigger source is set to the internal trigger (Internal), the change is ignored.

(2) This value is ignored for ENA E5061A/E5062A.
    �    Selects the trigger source.

Valid Values:
AGENA_TRIGGER_SOURCE_INTERNAL (0)
  - Uses the internal trigger to generate continuous triggers automatically.

AGENA_TRIGGER_SOURCE_EXTERNAL (1)
  - Generates a trigger when the trigger signal is inputted externally via the Ext Trig connector or the handler interface.

AGENA_TRIGGER_SOURCE_MANUAL   (2)
  - Generates a trigger when the key operation of [Trigger] - Trigger is executed from the front panel.

AGENA_TRIGGER_SOURCE_BUS      (3)
  - Generates a trigger when the *TRG command is executed.

Default Value:
AGENA_TRIGGER_SOURCE_INTERNAL (0)

Notes:
When you change the trigger source during sweep, the sweep is canceled.
   e=����  �    Status                           j %  �  �    Instrument Handle                j� > �       Continuous Sweep                 kl > % �  d    Channel                          l& >� �       Point Trigger                    m� � % � d    Trigger Source                     	               Enable VI_TRUE Disable VI_FALSE    1     Enable VI_TRUE Disable VI_FALSE               �Internal AGENA_TRIGGER_SOURCE_INTERNAL External AGENA_TRIGGER_SOURCE_EXTERNAL Manual AGENA_TRIGGER_SOURCE_MANUAL BUS AGENA_TRIGGER_SOURCE_BUS    1    This function configure limit test parameters.
    (    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Selects the corresponding channel for limit test configuration.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA E5061A/E5062A)

Default Value: 1
     �    For the active trace of selected channel, enables or disables the limit test function.

Valid Values:
VI_TRUE  (1) - Enable
VI_FALSE (0) - Disable

Default Value:
VI_FALSE (0)
     �    For the active trace of selected channel, enables or disables the limit line display.

Valid Values:
VI_TRUE  (1) - Enable
VI_FALSE (0) - Disable

Default Value:
VI_FALSE (0)
     �    Enables or disables the Fail display when the limit test fails.

Valid Values:
VI_TRUE  (1) - Enable
VI_FALSE (0) - Disable

Default Value:
VI_FALSE (0)
    R    For the active trace of selected channel, specifies whether to display the part of the limit line(s) that is not used for evaluation.

Valid Values:
VI_TRUE  (1) - Enable (Displays the clipped limit line(s))
VI_FALSE (0) - Disable (Displays the entire limit line(s))

Default Value:
VI_TRUE (1)

Notes:

(1) Only for ENA E5061A/E5062A.
   r�����  �    Status                           v� %  �  �    Instrument Handle                w� > % �  d    Channel                          xM > � �       Limit Test                       y >� �       Limit Line Display               y� � � �       Limit Fail Display               zc � @ �       Limit Line Clip                    	               1     Enable VI_TRUE Disable VI_FALSE     Enable VI_TRUE Disable VI_FALSE     Enable VI_TRUE Disable VI_FALSE    Enable VI_TRUE Disable VI_FALSE    &    This function sets the limit table.
    ^    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Number of Lines) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Selects the corresponding channel for limit test configuration.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA E5061A/E5062A)

Default Value: 1
     �    Sets the number of lines.

Valid Range:
0 to 100

Default Value:
0

Notes:
If you set the number of lines to 0 you clear the limit table.     �    Pass the type of the limit line array.

Valid Values for each element:
AGENA_LIMIT_LINE_TYPE_OFF   (0) - Off
AGENA_LIMIT_LINE_TYPE_UPPER (1) - Upper limit line
AGENA_LIMIT_LINE_TYPE_LOWER (2) - Lower limit line
     S    Pass the value on the horizontal axis (frequency/power/time) of
the start point.
     Q    Pass the value on the horizontal axis (frequency/power/time) of
the end point.
     :    Pass the value on the vertical axis of the start point.
     8    Pass the value on the vertical axis of the end point.
   }�����  �    Status                           �e %  �  �    Instrument Handle                � > % �  d    Channel                          �� > � �  d    Number of Lines                  �T >� �  d    Type of the Line                 �1 � % �  d    Start Point X Value              �� � � �  d    End Point X Value                �� �� �  d    Start Point Y Value              �' � % �  d    End Point Y Value                  	               1    0                        "    This function configure marker.
     �    Selects the corresponding channel for marker configuration.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA E5061A/E5062A)

Default Value: 1
     �    Selects the corresponding marker.

Valid Range: 1 to 10
1 to 9 - marker1 to marker9
10     - reference marker

Default Value: 1
    �    For the active trace of selected channel, sets the stimulus value of selected marker.

Units: Hz, dBm or second

Valid Range:
Sweep start value to sweep stop value

Default Value:
0.0

Notes:
(1) When the reference marker mode is enabled, it is the value relative to the reference marker.

(2) When the span value of the sweep range is 0, the range is from 0 to sweep time value.

(3) When the span value of the sweep range is 0, the unit is 0.    $    For the active trace of selected channel, enables or disables the display of selected marker.
The display of the reference marker is turned on or off when you turn on or off the reference marker mode.

Valid Values:
VI_TRUE  (1) - Enable
VI_FALSE (0) - Disable

Default Value:
VI_FALSE (0)
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Marker) out of range.
BFFC0005  Parameter 5 (Unit) out of range.
BFFC0006  Parameter 6 (State) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.   �� > % � d    Channel                          �U > � � d    Marker                           �� � % � d    Stimulus                         �� � � �       State                            �� %  �  �    Instrument Handle                �p����  �    Status                             1    1    1.0e6     Enable VI_TRUE Disable VI_FALSE        	           W    For the active trace of selected channel, sets selected marker to the active marker.
    x    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Marker) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Selects the corresponding channel.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA E5061A/E5062A)

Default Value: 1
     �    Selects the corresponding marker.

Valid Range: 1 to 10
1 to 9 - marker1 to marker9
10     - reference marker

Default Value: 1
   �*����  �    Status                           �� %  �  �    Instrument Handle                �I > % � d    Channel                          �� > � �  d    Marker                             	               1    1    '    This function configure marker mode.
     �    Selects the corresponding channel for marker mode configuration.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA E5061A/E5062A)

Default Value: 1
     �    For selected channel, enables or disables the marker coupling
between traces.

Valid Values:
VI_TRUE  (1) - Enable
VI_FALSE (0) - Disable

Default Value:
VI_FALSE (0)
        For the active trace of selected channel, enables or disables the discrete mode (mode in which the marker moves only at the measurement points) with selected marker.

Valid Range:
VI_TRUE  (1) - Discrete
VI_FALSE (0) - Continuous

Default Value:
VI_TRUE (1)
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Coupled) out of range.
BFFC0004  Parameter 4 (Marker Mode) out of range.
BFFC0005  Parameter 5 (Reference Marker Mode) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.        For the active trace of selected channel, enables or disables the reference marker mode.
The reference marker mode is turned on or off when you turn on or off the display of the reference marker.

Valid Values:
VI_TRUE  (1) - Enable
VI_FALSE (0) - Disable

Default Value:
VI_FALSE (0)
   �� @ ) � d    Channel                          �N < � �       Coupled                          �� <w �       Marker Mode                      � %  �  �    Instrument Handle                ������  �    Status                           �� � H �       Reference Marker Mode              1     Enable VI_TRUE Disable VI_FALSE  % Discrete VI_TRUE Continuous VI_FALSE        	            Enable VI_TRUE Disable VI_FALSE    )    This function configure marker search.
    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Marker) out of range.
BFFC0004  Parameter 4 (Range Coupling) out of range.
BFFC0005  Parameter 5 (Tracking) out of range.
BFFC0006  Parameter 6 (Peak Excursion) out of range.
BFFC0007  Parameter 7 (Peak Polarity) out of range.
BFFC0008  Parameter 8 (Target Value) out of range.
BFFC0009  Parameter 9 (Target Polarity) out of range.
BFFC0010  Parameter 10 (Partial Marker State) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Selects the corresponding channel for marker search configuration.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA E5061A/E5062A)

Default Value: 1
     �    For the active trace of selected channel, enables or disables the search tracking (function to repeat the search for each sweep) of selected marker.

Valid Values:
VI_TRUE  (1) - Enable
VI_FALSE (0) - Disable

Default Value:
VI_FALSE (0)
    )    For selected channel, specifies whether to set the coupling of
the marker search range for all traces.

Valid Values:
VI_TRUE  (1) - Enable
  - Specifies the search range with the trace coupling.

VI_FALSE (0) - Disable
  - Specifies the search range for each trace.

Default Value:
VI_TRUE (1)
        Selects the corresponding marker.

Valid Range: 0 to 10
1 to 9 - marker1 to marker9
10     - reference marker

Default Value: 1

Notes:
If marker = 0, apply tracking, peak excursion, peak polarity, target value  and target polarity for the multi peak search.     �    For the active trace of selected channel, sets the lower limit for the peak excursion value of selected marker.

Valid Range:
0.0 to 5.0e8

Default Value:
3.0
    �    For the active trace of selected channel, selects the polarity of the peak to be searched with selected marker.

Valid Values:
AGENA_MARKER_PEAK_POLARITY_POSITIVE (0)
   - the positive peak

AGENA_MARKER_PEAK_POLARITY_NEGATIVE (1)
  - the negative peak

AGENA_MARKER_PEAK_POLARITY_BOTH     (2)
  - both the positive and the negative peak.

Default Value:
AGENA_MARKER_PEAK_POLARITY_POSITIVE (0)
     �    For the active trace of selected channel, sets the target value to be searched with selected marker.

Valid Range:
-5.0e8 to 5.0e8

Default Value:
0.0
    {    For the active trace of selected channel, sets the target value to be searched with selected marker.

Valid Values:
AGENA_MARKER_TARGET_POLARITY_POSITIVE (0)
   - the positive

AGENA_MARKER_TARGET_POLARITY_NEGATIVE (1)
  - the negative

AGENA_MARKER_TARGET_POLARITY_BOTH     (2)
  - both the positive and the negative.

Default Value:
AGENA_MARKER_TARGET_POLARITY_POSITIVE (0)
    $    For selected channel, sets whether to use an arbitrary range
when executing the marker search.
When the trace coupling is disabled, the active trace is the target to be set.

Valid Values:
VI_TRUE  (1) - An arbitrary range
VI_FALSE (0) - The entire sweep range

Default Value:
VI_FALSE (0)
     �    For selected channel, sets the start value of the marker search
range.
When the trace coupling is disabled, the active trace is the target to be set.

Default Value:
0.0
     �    For selected channel, sets the stop value of the marker search
range.
When the trace coupling is disabled, the active trace is the target to be set.

Default Value:
0.0
   ������  �    Status                           �� %  �  �    Instrument Handle                �C >  � d    Channel                          � >� �       Tracking                         �� >D �       Range Coupling                   �, > � �  d    Marker                           �8 �  �  d    Peak Excursion                   �� � � � d    Peak Polarity                    �v �9 �  d    Target Value                     � �� � d    Target Polarity                  �� � ? 	�       Partial Marker State             �� � � 
�  d    Start                            �z �9 �  d    Stop                               	               1     Enable VI_TRUE Disable VI_FALSE    Enable VI_TRUE Disable VI_FALSE    1    3.0               Positive AGENA_MARKER_PEAK_POLARITY_POSITIVE Negative AGENA_MARKER_PEAK_POLARITY_NEGATIVE Both AGENA_MARKER_PEAK_POLARITY_BOTH    0.0               �Positive AGENA_MARKER_TARGET_POLARITY_POSITIVE Negative AGENA_MARKER_TARGET_POLARITY_NEGATIVE Both AGENA_MARKER_TARGET_POLARITY_BOTH    On VI_TRUE Off VI_FALSE    0.0    0.0    3    This function configure bandwidth marker search.
    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Marker) out of range.
BFFC0004  Parameter 4 (State) out of range.
BFFC0005  Parameter 5 (Bandwidth Definition Value) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Selects the corresponding channel for bandwidth marker search configuration.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA E5061A/E5062A)

Default Value: 1
     �    For the active trace of selected channel, enables or disables the bandwidth search result display.

Valid Values:
VI_TRUE  (1) - Enable
VI_FALSE (0) - Disable

Default Value:
VI_FALSE (0)
     �    For the active trace of selected channel, sets the bandwidth definition value of selected marker.

Valid Range:
-5.0e8 to 5.0e8

Default Value:
-3.0
     �    Selects the corresponding marker.

Valid Range: 1 to 10
1 to 9 - marker1 to marker9
10     - reference marker

Default Value: 1
   ������  �    Status                           �� %  �  �    Instrument Handle                �^ > % � d    Channel                          �( >� �       State                            �� � % �  d    Bandwidth Definition Value       č > � �  d    Marker                             	               1     Enable VI_TRUE Disable VI_FALSE    -3.0    1    m    This function configure marker function.

Notes:
(1) This function is available only for ENA E5061A/E5062A.    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Marker) out of range.
BFFC0004  Parameter 4 (Range Coupling) out of range.
BFFC0005  Parameter 5 (Tracking) out of range.
BFFC0006  Parameter 6 (Peak Excursion) out of range.
BFFC0007  Parameter 7 (Peak Polarity) out of range.
BFFC0008  Parameter 8 (Target Value) out of range.
BFFC0009  Parameter 9 (Target Polarity) out of range.
BFFC0010  Parameter 10 (Partial Marker State) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Selects the corresponding channel for marker search configuration.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA E5061A/E5062A)

Default Value: 1
    .    For the active trace of channel, turn on and off the marker function.

Valid Values:
AGENA_MARKER_MATH_FLAT (0)
   - marker flatness function.

AGENA_MARKER_MATH_FST  (1)
  - RF filter statistics.

AGENA_MARKER_MATH_STAT (2)
  - marker statistics function.

Default Value:
AGENA_MARKER_MATH_FLAT (0)
     �    For the active trace of selected channel, enables or disables the marker function.

Valid Values:
VI_TRUE  (1) - Enable
VI_FALSE (0) - Disable

Default Value:
VI_FALSE (0)   �|���  �    Status                           �   �  �    Instrument Handle                ͠ K i � d    Channel                          �` K � � d    Marker Function                  ϖ G� �       State                              	               1               mFlatness AGENA_MARKER_MATH_FLAT RF Filter Statistics AGENA_MARKER_MATH_FST Statistics AGENA_MARKER_MATH_STAT    On 1 Off 0    r    This function configure notch marker search.

Notes:
(1) This function is available only for ENA E5061A/E5062A.
    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Marker) out of range.
BFFC0004  Parameter 4 (Range Coupling) out of range.
BFFC0005  Parameter 5 (Tracking) out of range.
BFFC0006  Parameter 6 (Peak Excursion) out of range.
BFFC0007  Parameter 7 (Peak Polarity) out of range.
BFFC0008  Parameter 8 (Target Value) out of range.
BFFC0009  Parameter 9 (Target Polarity) out of range.
BFFC0010  Parameter 10 (Partial Marker State) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Selects the corresponding channel for bandwidth marker search configuration.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA E5061A/E5062A)

Default Value: 1
     �    For the active trace of selected channel, enables or disables the notch search result display.

Valid Values:
VI_TRUE  (1) - Enable
VI_FALSE (0) - Disable

Default Value:
VI_FALSE (0)
     �    For the active trace of selected channel, sets the notch definition value of selected marker.

Valid Range:
-5.0e8 to 5.0e8

Default Value:
-3.0
     �    Selects the corresponding marker.

Valid Range: 1 to 10
1 to 9 - marker1 to marker9
10     - reference marker

Default Value: 1
   �m}���  �    Status                           �_   �  �    Instrument Handle                �� > A � d    Channel                          �� >� �       State                            ڊ � A �  d    Notch Definition Value           �% > � �  d    Marker                             	               1     Enable VI_TRUE Disable VI_FALSE    -3.0    1    /    This function configure analysis parameters.
    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Analysis Type) out of range.
BFFC0004  Parameter 4 (Range Coupling) out of range.
BFFC0005  Parameter 5 (Peak Excursion) out of range.
BFFC0006  Parameter 6 (Filter Type) out of range.
BFFC0007  Parameter 7 (Filter Function) out of range.
BFFC0008  Parameter 8 (Tracking) out of range.
BFFC0009  Parameter 9 (Partial Range Analysis) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Selects the corresponding channel for analysis configuration.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA E5061A/E5062A)

Default Value: 1
     �    For selected channel, specifies whether to set the coupling of
the analysis range of the agena_actExecuteAnalysis function for all traces.

Valid Values:
VI_TRUE  (1) - Enable
VI_FALSE (0) - Disable

Default Value:
VI_FALSE (0)
     �    For the active trace of selected channel, sets the lower limit for the peak excursion value when executing the peak search with the agena_actExecuteAnalysis function.

Valid Range:
0.0 to 5.0e8

Default Value:
3.0
     �    For the active trace of selected channel, selects the target value when performing the target search with the agena_actExecuteAnalysis function.

Valid Range:
-5.0e8 to 5.0e8

Default Value:
0.0
    �    For the active trace of selected channel, selects the type of analysis.

Valid Values:
AGENA_ANALYSIS_TYPE_PEAK_2_PEAK (0)
  - Specifies the analysis of the difference between the maximum value and the minimum value (Peak to Peak).

AGENA_ANALYSIS_TYPE_STD_DEV     (1)
  - Specifies the analysis of the standard deviation.

AGENA_ANALYSIS_TYPE_MEAN        (2)
  - Specifies the analysis of the mean value.

AGENA_ANALYSIS_TYPE_MAXIMUM     (3)
  - Specifies the search for the maximum value.

AGENA_ANALYSIS_TYPE_MINIMUM     (4)
  - Specifies the search for the minimum value.

AGENA_ANALYSIS_TYPE_PEAK        (5)
  - Specifies the search for the maximum positive (minimum negative) peak.

AGENA_ANALYSIS_TYPE_ALL_PEAK    (6)
  - Specifies the search for all peaks.

AGENA_ANALYSIS_TYPE_ALL_TARGET  (7)
  - Specifies the search for all targets.

Default Value:
AGENA_ANALYSIS_TYPE_PEAK_2_PEAK (0)
    �    For the active trace of selected channel, selects the polarity when performing the peak search with the agena_actExecuteAnalysis function.

Valid Values:
AGENA_ANALYSIS_PEAK_POLARITY_POSITIVE (0)
   - the positive peak

AGENA_ANALYSIS_PEAK_POLARITY_NEGATIVE (1)
  - the negative peak

AGENA_ANALYSIS_PEAK_POLARITY_BOTH     (2)
  - both the positive and the negative peak.

Default Value:
AGENA_ANALYSIS_PEAK_POLARITY_POSITIVE (0)
    �    For the active trace of selected channel, selects the transition type when performing the target search with the agena_actExecuteAnalysis function.

Valid Values:
AGENA_ANALYSIS_TARGET_POLARITY_POSITIVE (0)
   - the positive

AGENA_ANALYSIS_TARGET_POLARITY_NEGATIVE (1)
  - the negative

AGENA_ANALYSIS_TARGET_POLARITY_BOTH     (2)
  - both the positive and the negative.

Default Value:
AGENA_ANALYSIS_TARGET_POLARITY_POSITIVE (0)
    J    For selected channel, sets whether to use an arbitrary range
when executing the analysis with the agena_actExecuteAnalysis function.
When the trace coupling is disabled, the active trace is the target to be set.

Valid Values:
VI_TRUE  (1) - An arbitrary range
VI_FALSE (0) - The entire sweep range

Default Value:
VI_FALSE (0)
     �    For selected channel, sets the start value of the analysis range of the agena_actExecuteAnalysis function.
When the trace coupling is disabled, the active trace is the target to be set.

Default Value:
0.0
     �    For selected channel, sets the stop value of the analysis range
of the agena_actExecuteAnalysis function.
When the trace coupling is disabled, the active trace is the target to be set.

Default Value:
0.0
   �i����  �    Status                           �. %  �  �    Instrument Handle                �� > % � d    Channel                          � >� �       Range Coupling                   �v �  �  d    Peak Excursion                   �V �& �  d    Target Value                     �# > � � d    Analysis Type                    � � � � d    Peak Polarity                    �e �� � d    Target Polarity                  � � C �       Partial Range Analysis State     �q � � 	�  d    Start                            �I �& 
�  d    Stop                               	               1     Enable VI_TRUE Disable VI_FALSE    3.0    0.0              2Peak to Peak AGENA_ANALYSIS_TYPE_PEAK_2_PEAK Standard_deviation AGENA_ANALYSIS_TYPE_STD_DEV Mean AGENA_ANALYSIS_TYPE_MEAN Maximum AGENA_ANALYSIS_TYPE_MAXIMUM Minimum AGENA_ANALYSIS_TYPE_MINIMUM Peak AGENA_ANALYSIS_TYPE_PEAK All Peaks AGENA_ANALYSIS_TYPE_ALL_PEAK All Targets AGENA_ANALYSIS_TYPE_ALL_TARGET               �Positive AGENA_ANALYSIS_PEAK_POLARITY_POSITIVE Negative AGENA_ANALYSIS_PEAK_POLARITY_NEGATIVE Both AGENA_ANALYSIS_PEAK_POLARITY_BOTH               �Positive AGENA_ANALYSIS_TARGET_POLARITY_POSITIVE Negative AGENA_ANALYSIS_TARGET_POLARITY_NEGATIVE Both AGENA_ANALYSIS_TARGET_POLARITY_BOTH    On VI_TRUE Off VI_FALSE    0.0    0.0    n    This function configure fixture simulator.

Notes:

1) This function is not available for ENA E5061A/E5062A.    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (State) out of range.
BFFC0004  Parameter 4 (Balance Device Type) out of range.
BFFC0005  Parameter 5 (Display Property) out of range.
BFFC0006  Parameter 6 (Port 1) out of range.
BFFC0007  Parameter 7 (Port 2) out of range.
BFFC0008  Parameter 8 (Port 3) out of range.
BFFC0009  Parameter 9 (Port 4) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     q    Selects the corresponding channel for fixture simulator configuration.

Valid Range: 1 to 16

Default Value: 1
     �    Enables or disables the fixture simulator function of selected channel.

Valid Values:
VI_TRUE  (1) - Enable
VI_FALSE (0) - Disable

Default Value:
VI_FALSE (0)
    �    For selected channel, selects the balance device type of the fixture simulator function.

Valid Values:
AGENA_FIX_SIM_BALANCE_TYPE_SBAL  (0)
  - Specifies the unbalance-balance (3 ports).

AGENA_FIX_SIM_BALANCE_TYPE_BBAL  (1)
  - Specifies the balance-balance (4 ports).

AGENA_FIX_SIM_BALANCE_TYPE_SSBAL (2)
  - Specifies the unbalance-unbalance-balance (4 ports).

Default Value:
AGENA_FIX_SIM_BALANCE_TYPE_SBAL  (0)
     _    Sets port number assigned to logical port 1 (port a).

Valid Range:
1 to 4

Default Value:
1
    	    Sets port number assigned to logical port 1 (port b) when Balance Device Type is set to AGENA_FIX_SIM_BALANCE_TYPE_BBAL.

Sets port number assigned to logical port 2 (port b) when Balance Device Type is set to other types.


Valid Range:
1 to 4

Default Value:
2
    	    Sets port number assigned to logical port 3 (port c) when Balance Device Type is set to AGENA_FIX_SIM_BALANCE_TYPE_SSBAL.

Sets port number assigned to logical port 2 (port c) when Balance Device Type is set to other types.

Valid Range:
1 to 4

Default Value:
3
    �    Sets port number assigned to logical port 3 (port d) when Balance Device Type is set to AGENA_FIX_SIM_BALANCE_TYPE_SSBAL.

Sets port number assigned to logical port 2 (port d) when Balance Device Type is set to AGENA_FIX_SIM_BALANCE_TYPE_BBAL.

Valid Range:
1 to 4

Default Value:
4

Notes:
This control is not used when Balance Device Type is set to AGENA_FIX_SIM_BALANCE_TYPE_SBAL.
     �    For selected channel, enables or disables the property display for the topology setting when using the balance-unbalance conversion.

Valid Values:
VI_TRUE  (1) - Enable
VI_FALSE (0) - Disable

Default Value:
VI_FALSE (0)
   ������  �    Status                           �� %  �  �    Instrument Handle                �3 > % � d    Channel                          �� > � �       State                            �W > � �    Balance Device Type                � % �  d    Port 1                            k � � �  d    Port 2                           | � �  d    Port 3                           � �� �  d    Port 4                            >� �       Display Property                   	               1     Enable VI_TRUE Disable VI_FALSE               �Unbalance - Balance AGENA_FIX_SIM_BALANCE_TYPE_SBAL Balance - Balance AGENA_FIX_SIM_BALANCE_TYPE_BBAL Unbalance - Unbalance - Balance AGENA_FIX_SIM_BALANCE_TYPE_SSBAL    1    2    3    4     Enable VI_TRUE Disable VI_FALSE    y    This function configure balance unbalance conversion.

Notes:

1) This function is not available for ENA E5061A/E5062A.    i    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Trace) out of range.
BFFC0004  Parameter 4 (State) out of range.
BFFC0005  Parameter 5 (Balance Device Type) out of range.
BFFC0006  Parameter 6 (Paremeter) out of range.
BFFC0007  Parameter 7 (Port 1) out of range.
BFFC0008  Parameter 8 (Port 2) out of range.



BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     M    Selects the corresponding channel.

Valid Range: 1 to 16

Default Value: 1
     �    For selected channel, enables or disables the balance-unbalance
conversion function for selected trace when the fixture simulator function is enabled.

Valid Values:
VI_TRUE  (1) - Enable
VI_FALSE (0) - Disable

Default Value:
VI_FALSE (0)
    b    For selected channel, sets the measurement parameters of selected trace.

Valid Values:

AGENA_BALANCE_PARAMETER_SSS        (0)  - SSS
AGENA_BALANCE_PARAMETER_SDS        (1)  - SDS
AGENA_BALANCE_PARAMETER_SSD        (2)  - SSD
AGENA_BALANCE_PARAMETER_SCS        (3)  - SCS
AGENA_BALANCE_PARAMETER_SSC        (4)  - SSC
AGENA_BALANCE_PARAMETER_SDD        (5)  - SDD
AGENA_BALANCE_PARAMETER_SCD        (6)  - SCD
AGENA_BALANCE_PARAMETER_SDC        (7)  - SDC
AGENA_BALANCE_PARAMETER_SCC        (8)  - SCC
AGENA_BALANCE_PARAMETER_IMBALANCE1 (9)  - Imbalance 1
AGENA_BALANCE_PARAMETER_IMBALANCE2 (10) - Imbalance 2
AGENA_BALANCE_PARAMETER_IMBALANCE3 (11) - Imbalance 3
AGENA_BALANCE_PARAMETER_IMBALANCE4 (12) - Imbalance 4
AGENA_BALANCE_PARAMETER_CMRR1      (13) - CMRR1
AGENA_BALANCE_PARAMETER_CMRR2      (14) - CMRR2


Default Value:
AGENA_BALANCE_PARAMETER_SSS (0)
     K    Selects the corresponding trace.

Valid Range: 1 to 16

Default Value: 1
    �    For selected channel, selects the balance device type of the fixture simulator function.

Valid Values:
AGENA_FIX_SIM_BALANCE_TYPE_SBAL  (0)
  - Specifies the unbalance-balance (3 ports).

AGENA_FIX_SIM_BALANCE_TYPE_BBAL  (1)
  - Specifies the balance-balance (4 ports).

AGENA_FIX_SIM_BALANCE_TYPE_SSBAL (2)
  - Specifies the unbalance-unbalance-balance (4 ports).

Default Value:
AGENA_FIX_SIM_BALANCE_TYPE_SBAL  (0)
     V    Sets port number assigned to logical port 1.

Valid Range:
1 to 3

Default Value:
1
     V    Sets port number assigned to logical port 2.

Valid Range:
1 to 3

Default Value:
1
   �����  �    Status                           ( %  �  �    Instrument Handle                � >  � d    Channel                           > �       State                             �  � d    Parameter                        � > � �  d    Trace                            � >Z � �    Balance Device Type              � � � �  d    Port 1                           � � �  d    Port 2                             	               1     Enable VI_TRUE Disable VI_FALSE              $SSS AGENA_BALANCE_PARAMETER_SSS SDS AGENA_BALANCE_PARAMETER_SDS SSD AGENA_BALANCE_PARAMETER_SSD SCS AGENA_BALANCE_PARAMETER_SCS SSC AGENA_BALANCE_PARAMETER_SSC SDD AGENA_BALANCE_PARAMETER_SDD SCD AGENA_BALANCE_PARAMETER_SCD SDC AGENA_BALANCE_PARAMETER_SDC SCC AGENA_BALANCE_PARAMETER_SCC Imbalance 1 AGENA_BALANCE_PARAMETER_IMBALANCE1 Imbalance 2 AGENA_BALANCE_PARAMETER_IMBALANCE2 Imbalance 3 AGENA_BALANCE_PARAMETER_IMBALANCE3 Imbalance 4 AGENA_BALANCE_PARAMETER_IMBALANCE4 CMRR1 AGENA_BALANCE_PARAMETER_CMRR1 CMRR2 AGENA_BALANCE_PARAMETER_CMRR2    1               �Unbalance - Balance AGENA_FIX_SIM_BALANCE_TYPE_SBAL Balance - Balance AGENA_FIX_SIM_BALANCE_TYPE_BBAL Unbalance - Unbalance - Balance AGENA_FIX_SIM_BALANCE_TYPE_SSBAL    1    1    y    This function configure matching circuit embedding.

Notes:

(1) This function is not available for ENA E5061A/E5062A.
    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Port) out of range.
BFFC0004  Parameter 4 (State) out of range.
BFFC0005  Parameter 5 (Circuit Mode) out of range.
BFFC0006  Parameter 6 (Circuit Type) out of range.
BFFC0007  Parameter 7 (C) out of range.
BFFC0008  Parameter 8 (G) out of range.
BFFC0009  Parameter 9 (L) out of range.
BFFC0010  Parameter 10 (R) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     M    Selects the corresponding channel.

Valid Range: 1 to 16

Default Value: 1
     �    For all the ports of selected channel, enables or disables the
matching circuit embedding function when the fixture simulator function is enabled.

Valid Values:
VI_TRUE  (1) - Enable
VI_FALSE (0) - Disable

Default Value:
VI_FALSE (0)
     �    Sets port number.

Valid Range:
For Normal Mode:
1 to 4

For Differencial Mode:
1 to 2

Default Value:
1

Notes:
When the Circuit Mode control is set to AGENA_CIRCUIT_MODE_DIFFERNTIAL valid range is limited from 1 to 2.
     �    For selected port or selected balance port of selected channel,
sets the C value of the normal or differential matching circuit.

Valid Range:
-1.0e18 to 1.0e18 farad (F)

Default Value:
0.0 farad (F)
    �    For selected port or selected balance port of selected channel, selects the type of the normal or differential matching circuit.

If you want to select the user-defined circuit, you must specify the 2-port touchstone file in which the proper information on the user-defined circuit is saved in advance. If you do not specify the appropriate file and you select the user-defined circuit, an error occurs and AGENA_CIRCUIT_TYPE_NONE is automatically selected.

Valid Values:
AGENA_CIRCUIT_TYPE_NONE (0)
  - No-circuit

AGENA_CIRCUIT_TYPE_SLPC (1)
  - Circuit that consists of series L and shunt C

AGENA_CIRCUIT_TYPE_PCSL (2)
  - Circuit that consists of shunt L and series C

AGENA_CIRCUIT_TYPE_PLSC (3)
  - Circuit that consists of shunt C and series L

AGENA_CIRCUIT_TYPE_SCPL (4)
  - Circuit that consists of series C and shunt L

AGENA_CIRCUIT_TYPE_PLPC (5)
  - Circuit that consists of shunt L and shunt C

AGENA_CIRCUIT_TYPE_USER (6)
  - User-defined circuit

Default Value:
AGENA_CIRCUIT_TYPE_NONE (0)
     �    For selected port or selected balance port of selected channel,
sets the G value of the normal or differential matching circuit.

Valid Range:
-1.0e18 to 1.0e18 siemens (S)

Default Value:
0.0 siemens (S)
     �    For selected port or selected balance port of selected channel,
sets the L value of the normal or differential matching circuit.

Valid Range:
-1.0e18 to 1.0e18 henry (H)

Default Value:
0.0 henry (H)
     �    For selected port or selected balance port of selected channel,
sets the R value of the normal or differential matching circuit.

Valid Range:
-1.0e18 to 1.0e18 ohms

Default Value:
0.0 ohms
    �    For selected port or selected balance port of selected channel, specifies the file in which the information on the user-defined normal or differential matching circuit is saved (2-port touchstone file).

Specify the file name with the .s2p extension. If you want to specify a file on the floppy disk drive, you need to add "A:" at the beginning of the file name. When you use directory names and file name, separate them with "/" (slash) or "\" (backslash).

Notes:
Only for USER circuit type.
     �    Select matching circuit mode.

Valid Values:
AGENA_CIRCUIT_MODE_NORMAL       (0)
AGENA_CIRCUIT_MODE_DIFFERENTIAL (1)

Default Value:
AGENA_CIRCUIT_MODE_NORMAL (0)
   �����  �    Status                           !{ %  �  �    Instrument Handle                " >  � d    Channel                          "o > � �       State                            #e > � �  d    Port                             $K �  �  d    C                                % >� � d    Circuit Type                     ) � � �  d    G                                )� �- �  d    L                                *� �� 	�  d    R                                +� �  
�  �    File Name                        -� >G � d    Circuit Mode                       	               1     Enable VI_TRUE Disable VI_FALSE    1    0.0              None AGENA_CIRCUIT_TYPE_NONE Series L Shunt C AGENA_CIRCUIT_TYPE_SLPC Shunt C Series L AGENA_CIRCUIT_TYPE_PCSL Shunt L Series C AGENA_CIRCUIT_TYPE_PLSC Series C Shunt L AGENA_CIRCUIT_TYPE_SCPL Shunt L Shunt C AGENA_CIRCUIT_TYPE_PLPC User AGENA_CIRCUIT_TYPE_USER    0.0    0.0    0.0    ""              NDifferential AGENA_CIRCUIT_MODE_DIFFERENTIAL Normal AGENA_CIRCUIT_MODE_NORMAL    v    This function configure port impedance conversion.

Notes:

1) This function is not available for ENA E5061A/E5062A.    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Port) out of range.
BFFC0004  Parameter 4 (State) out of range.
BFFC0005  Parameter 5 (Circuit Mode) out of range.
BFFC0006  Parameter 6 (Z0) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     M    Selects the corresponding channel.

Valid Range: 1 to 16

Default Value: 1
        For all the normal or balance ports of selected channel, enables or disables the normal, common, differential port impedance conversion function when the fixture simulator function is enabled.

Valid Values:
VI_TRUE  (1) - Enable
VI_FALSE (0) - Disable

Default Value:
VI_FALSE (0)
     �    Sets port number.

Valid Range:
1 to 4

Default Value:
1

Notes:
When the Circuit Mode control is set to AGENA_CIRCUIT_MODE_DIFFERNTIAL valid range is limited from 1 to 2.
     �    For all the normal or balance ports of selected channel, sets the impedance value for the normal, common or differential port impedance conversion function.

Valid Range:
1.0e-3 to 1.0e7 ohms

Default Value:
50.0 ohms     �    Select matching circuit mode.

Valid Values:
AGENA_CIRCUIT_MODE_NORMAL       (0) - Normal
AGENA_CIRCUIT_MODE_DIFFERENTIAL (1) - Differential
AGENA_CIRCUIT_MODE_COMMON       (2) - Commom


Default Value:
AGENA_CIRCUIT_MODE_DIFFERENTIAL (1)
   2�����  �    Status                           8 %  �  �    Instrument Handle                8� H  � d    Channel                          8� H � �       State                            : H � �  d    Port                             :� H� �  d    Z0                               ;� HD � d    Circuit Mode                       	               1     Enable VI_TRUE Disable VI_FALSE    1    50.0              oCommon AGENA_CIRCUIT_MODE_COMMON Differential AGENA_CIRCUIT_MODE_DIFFERENTIAL Normal AGENA_CIRCUIT_MODE_NORMAL    s    This function configure network de-embedding.

Notes:

(1) This function is not available for ENA E5061A/E5062A.
    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Port) out of range.
BFFC0004  Parameter 4 (State) out of range.
BFFC0005  Parameter 5 (Circuit Type) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     M    Selects the corresponding channel.

Valid Range: 1 to 16

Default Value: 1
     �    For all the ports of selected channel, enables or disables the
network de-embedding function when the fixture simulator function is enabled.

Valid Values:
VI_TRUE  (1) - Enable
VI_FALSE (0) - Disable

Default Value:
VI_FALSE (0)
     ;    Sets port number.

Valid Range:
1 to 4

Default Value:
1
    b    For selected port of selected channel, selects the type of the network de-embedding.
If you want to select the user-defined network de-embedding, you must specify the 2-port touchstone file in which the information on the user-defined network is saved in advance.
If you do not specify the appropriate file and you select the user-defined network de-embedding, an error occurs and NONE is automatically selected.

Valid Values:
AGENA_NETWORK_DEEMBEDDING_NONE (0)
  - No-de-embedding.
AGENA_NETWORK_DEEMBEDDING_USER (1)
  - User-defined network de-embedding

Default Value:
AGENA_NETWORK_DEEMBEDDING_NONE (0)
    �    For selected port of selected channel, specifies the file in which the information on the user-defined network for the network de-embedding function is saved (2-port touchstone file).

Specify the file name with the .s2p extension. If you want to specify a file on the floppy disk drive, you need to add "A:" at the beginning of the file name. When you use directory names and file name, separate them with "/" (slash) or "\" (backslash).

Notes:
(1) Only for USER circuit type.

(2) Maximum 254 characters.
   ?\����  �    Status                           D9 %  �  �    Instrument Handle                D� > % � d    Channel                          E- >M �       State                            F > � �  d    Port                             F` >� � d    Circuit Type                     H� �M �  �    File Name                          	               1     Enable VI_TRUE Disable VI_FALSE    1               HNone AGENA_NETWORK_DEEMBEDDING_NONE User AGENA_NETWORK_DEEMBEDDING_USER    ""    �    This function configure 4-port network embedding/deembedding.

Notes:
(1) This function is available with the firmware version 3.50 or greater.

(2) This function is not available for ENA E5061A/E5062A.
    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (State) out of range.
BFFC0004  Parameter 4 (Topology Type) out of range.
BFFC0005  Parameter 5 (Port 1) out of range.
BFFC0006  Parameter 6 (Port 2) out of range.
BFFC0007  Parameter 7 (Port 3) out of range.
BFFC0008  Parameter 8 (Port 4) out of range.
BFFC0009  Parameter 9 (Network) out of range.
BFFC0010  Parameter 10 (Network Type) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     M    Selects the corresponding channel.

Valid Range: 1 to 16

Default Value: 1
     �    For selected channel, enables or disables the 4-port network embedding/de-embedding feature when the fixture simulator feature is enabled.

Valid Values:
VI_TRUE  (1) - Enable
VI_FALSE (0) - Disable

Default Value:
VI_FALSE (0)
     B    Sets the network number.

Valid Range:
1 to 2

Default Value: 1
     H    Sets the test port assignment.

Valid Range:
1 to 4

Default Value: 1
        For the 4-port network embedding/de-embedding feature for selected channel, selects a connection type.

Valid Values:
AGENA_TOPOLOGY_TYPE_A (0)
  - Specifies the type (Topology A) to connect between the 2 ports of the analyzer and the DUT.

AGENA_TOPOLOGY_TYPE_B (1)
  - Specifies the type (Topology B) to connect between the 3 ports of the analyzer and the DUT.

AGENA_TOPOLOGY_TYPE_C (2)
  - Specifies the type (Topology C) to connect between the 3 ports of the analyzer and the DUT.

Default Value:
AGENA_TOPOLOGY_TYPE_A (0)
     H    Sets the test port assignment.

Valid Range:
1 to 4

Default Value: 2
     �    Sets the test port assignment.

Valid Range:
1 to 4

Default Value: 3

Notes:
(1) This control is not used when the Topology Type is set to AGENA_TOPOLOGY_TYPE_A.
     �    Sets the test port assignment.

Valid Range:
1 to 4

Default Value: 4

Notes:
(1) This control is not used when the Topology Type is set to AGENA_TOPOLOGY_TYPE_A or AGENA_TOPOLOGY_TYPE_B.
    �    For selected channel, specifies a file in which the information of selected network you want to embed/de-embed using the 4-port network embedding/de-embedding feature is saved (4-port touchstone file). 
Specify a file name with the extension ".s4p." If you want to specify a file on the floppy disk drive, you need to add "A:" at the beginning of the file name. When you use directory names and file name, separate them with "/" (slash) or "\" (backslash).
    J    For the 4-port network embedding/de-embedding feature for selected channel, selects a network processing type for selected network.

Valid Values:
AGENA_NETWORK_TYPE_NONE    (0) - No-processing
AGENA_NETWORK_TYPE_EMBED   (1) - Emabedding
AGENA_NETWORK_TYPE_DEEMBED (2) - De-embedding

Default Value:
AGENA_NETWORK_TYPE_NONE (0)
   M�����  �    Status                           S{ %  �  �    Instrument Handle                T > % � d    Channel                          To > � �       State                            U] � % �  d    Network                          U�  % �  d    Port 1                           U� >� � d    Topology Type                    X  � �  d    Port 2                           Xa / �  d    Port 3                           Y � �  d    Port 4                           Y� �/ 
�  �    Network File                     [� � � 	� d    Network Type                       	               1     Enable VI_TRUE Disable VI_FALSE    1    1               HA AGENA_TOPOLOGY_TYPE_A B AGENA_TOPOLOGY_TYPE_B C AGENA_TOPOLOGY_TYPE_C    2    3    4    ""               hNone AGENA_NETWORK_TYPE_NONE Embedding AGENA_NETWORK_TYPE_EMBED De-embedding AGENA_NETWORK_TYPE_DEEMBED    6    This function configure time domain transformation.
    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (State) out of range.
BFFC0004  Parameter 4 (Transformation Type) out of range.
BFFC0005  Parameter 5 (Stimulus Type) out of range.
BFFC0006  Parameter 6 (Beta) out of range.
BFFC0007  Parameter 7 (Impluse Width) out of range.
BFFC0008  Parameter 8 (Rise Time of Step Signal) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Selects the corresponding channel.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA E5061A/E5062A)

Default Value: 1
    �    For the active trace of selected channel, enables or disables the transformation function of the time domain function.

Valid Values:
VI_TRUE  (1) - Enable
VI_FALSE (0) - Disable

Default Value:
VI_FALSE (0)

Notes:
(1) You can enable the transformation function only when the sweep type is the linear sweep and the number of points is 3 or more. 

(2) When the sweep type is the power sweep, you cannot enable the transformation function.
     �    For the active trace of selected channel, sets the shape of the Kayser Bessel window using Beta used for the transformation function of the time domain function.

Valid Range:
0 to 13

Default Value: 6
    0    For the active trace of selected channel, selects the transformation type used for the transformation function of the time domain function.

Valid Values:
AGENA_TRANSFORMATION_TYPE_BPASS (0) - Band-pass
AGENA_TRANSFORMATION_TYPE_LPASS (1) - Low-pass

Default Value:
AGENA_TRANSFORMATION_TYPE_BPASS (0)
        For the active trace of selected channel, sets the shape of the Kayser Bessel window using the impulse width used for the transformation function of the time domain function.

Valid Range:
Varies depending on the frequency span and the transformation type.

Default Value:
0.0
        For the active trace of selected channel, sets the shape of the Kayser Bessel window using the rise time of step signal used for the transformation function of the time domain function.

Valid Range:
Varies depending on the frequency span.

Default Value: 0.0
    6    For the active trace of selected channel, selects the stimulus type used for the transformation function of the time domain function.

Valid Values:
AGENA_TRANSFORM_STIMULUS_TYPE_IMPULSE (0) - Impulse
AGENA_TRANSFORM_STIMULUS_TYPE_STEP    (1) - Step

Default Value:
AGENA_TRANSFORM_STIMULUS_TYPE_IMPULSE (0)
   `�����  �    Status                           fc %  �  �    Instrument Handle                g > % � d    Channel                          g� > � �       State                            id � % �  d    Beta                             j8 > � d    Transformation Type              kp � � �  d    Impluse Width                    l� �) �  d    Rise Time of Step Signal         m� >� � d    Stimulus Type                      	               1     Enable VI_TRUE Disable VI_FALSE    6               SBand-pass AGENA_TRANSFORMATION_TYPE_BPASS Low-pass AGENA_TRANSFORMATION_TYPE_LPASS    0.0    0.0               VImpulse AGENA_TRANSFORM_STIMULUS_TYPE_IMPULSE Step AGENA_TRANSFORM_STIMULUS_TYPE_STEP    5    This function configure time domain display range.
    ~    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Setting Type) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Selects the corresponding channel.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA E5061A/E5062A)

Default Value: 1
     �    For the active trace of selected channel, selects the start value used for the transformation function of the time domain function.

Valid Range:
Varies depending on the frequency span and the number of
points.

Default Value:
0.0
     �    For the active trace of selected channel, selects the stop value used for the transformation function of the time domain function.

Valid Range:
Varies depending on the frequency span and the number of
points.

Default Value:
1.0e-8     �    Selects type of setting.

Valid Values:
AGENA_TIME_DOMAIN_SET_TYPE_CENTER_SPAN (0) - Sets Center / Span
AGENA_TIME_DOMAIN_SET_TYPE_START_STOP  (1) - Sets Start / Stop

Default Value:
AGENA_TIME_DOMAIN_SET_TYPE_START_STOP (1)
     �    For the active trace of selected channel, selects the center value used for the transformation function of the time domain function.

Valid Range:
Varies depending on the frequency span and the number of
points.

Default Value:
0.0
     �    For the active trace of selected channel, selects the span value used for the transformation function of the time domain function.

Valid Range:
Varies depending on the frequency span and the number of
points.

Default Value:
2.0e-8   r����  �    Status                           v� %  �  �    Instrument Handle                w, > % � d    Channel                          w� � % �  d    Start                            x� � � �  d    Stop                             y� > � � d    Setting Type                     z� �D �  d    Center                           {� �� �  d    Span                               	               1    0.0    1.0e-8              dCenter/Span AGENA_TIME_DOMAIN_SET_TYPE_CENTER_SPAN Start/Stop AGENA_TIME_DOMAIN_SET_TYPE_START_STOP    0.0    2.0e-8    o    This function configure time domain gating.

Notes:
(1) This function is not available for ENA E5061A/E5062A.        This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (State) out of range.
BFFC0004  Parameter 4 (Gate Type) out of range.
BFFC0005  Parameter 5 (Gate Shape) out of range.
BFFC0006  Parameter 6 (Setting Type) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     M    Selects the corresponding channel.

Valid Range: 1 to 16

Default Value: 1
    �    For the active trace of selected channel, enables or disables the gating function of the time domain function.

Valid Values:
VI_TRUE  (1) - Enable
VI_FALSE (0) - Disable

Default Value:
VI_FALSE (0)

Notes:
(1) You can enable the gating function only when the sweep type is the linear sweep and the number of points is 3 or more.

(2) When the sweep type is the power sweep, you cannot enable the gating function.    +    For the active trace of selected channel, selects the gate type used for the gating function of the time domain function.

Valid Values:
AGENA_TIME_DOMAIN_GATE_TYPE_BPASS (0) - Band-pass type
AGENA_TIME_DOMAIN_GATE_TYPE_NOTCH (1) - Notch type

Default Value:
AGENA_TIME_DOMAIN_GATE_TYPE_BPASS (0)
    �    For the active trace of selected channel, selects the shape of the gate used for the gating function of the time domain function.

Valid Values:
AGENA_TIME_DOMAIN_GATE_SHAPE_MAX    (0) - Maximum shape
AGENA_TIME_DOMAIN_GATE_SHAPE_WIDE   (1) - Wide shape
AGENA_TIME_DOMAIN_GATE_SHAPE_NORMAL (2) - Normal shape
AGENA_TIME_DOMAIN_GATE_SHAPE_MIN    (3) - Minimum shape

Default Value:
AGENA_TIME_DOMAIN_GATE_SHAPE_NORMAL (2)
     �    Selects type of setting.

Valid Values:
AGENA_TIME_DOMAIN_SET_TYPE_CENTER_SPAN (0) - Sets Center / Span
AGENA_TIME_DOMAIN_SET_TYPE_START_STOP  (1) - Sets Start / Stop

Default Value:
AGENA_TIME_DOMAIN_SET_TYPE_START_STOP (1)
     �    For the active trace of selected channel, selects the start value used for the transformation function of the time domain function.

Valid Range:
Varies depending on the frequency span and the number of
points.

Default Value:
0.0
     �    For the active trace of selected channel, selects the stop value used for the transformation function of the time domain function.

Valid Range:
Varies depending on the frequency span and the number of
points.

Default Value:
1.0e-8     �    For the active trace of selected channel, selects the center value used for the transformation function of the time domain function.

Valid Range:
Varies depending on the frequency span and the number of
points.

Default Value:
0.0
     �    For the active trace of selected channel, selects the span value used for the transformation function of the time domain function.

Valid Range:
Varies depending on the frequency span and the number of
points.

Default Value:
2.0e-8   G����  �    Status                           �Z %  �  �    Instrument Handle                �� > % � d    Channel                          �N > � �       State                            �� > � � d    Gate Type                        �) >v � d    Gate Shape                       �� � � � d    Setting Type                     �� � % �  d    Start                            �� � � �  d    Stop                             �� �/ �  d    Center                           �� �� 	�  d    Span                               	               1     Enable VI_TRUE Disable VI_FALSE               TBand-pass AGENA_TIME_DOMAIN_GATE_TYPE_BPASS Notch AGENA_TIME_DOMAIN_GATE_TYPE_NOTCH              �Maximum Shape AGENA_TIME_DOMAIN_GATE_SHAPE_MAX Wide Shape AGENA_TIME_DOMAIN_GATE_SHAPE_WIDE Normal Shape AGENA_TIME_DOMAIN_GATE_SHAPE_NORMAL Minimum Shape AGENA_TIME_DOMAIN_GATE_SHAPE_MIN              dCenter/Span AGENA_TIME_DOMAIN_SET_TYPE_CENTER_SPAN Start/Stop AGENA_TIME_DOMAIN_SET_TYPE_START_STOP    0.0    1.0e-8    0.0    2.0e-8    0    This function configure parameter conversion.
    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (State) out of range.
BFFC0004  Parameter 4 (Parameter) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    For the active trace of selected channel, enables or disables the parameter conversion function.

Valid Values:
VI_TRUE  (1) - Enable
VI_FALSE (0) - Disable

Default Value:
VI_FALSE (0)
    �    For the active trace of selected channel, select the parameter after conversion using the parameter conversion function.

Valid Values:
AGENA_PARAMETER_CONVERSION_ZREFLECT  (0)
  - The equivalent impedance in reflection measurement.

AGENA_PARAMETER_CONVERSION_ZTRANSMIT (1)
  - The equivalent impedance (series) in transmission measurement.

AGENA_PARAMETER_CONVERSION_YREFLECT  (2)
  - The equivalent admittance in reflection measurement.

AGENA_PARAMETER_CONVERSION_YTRANSMIT (3)
  - The equivalent edmittance (series) in transmission measurement.

AGENA_PARAMETER_CONVERSION_INVERSION (4)
  - the inverse S-parameter.

AGENA_PARAMETER_CONVERSION_ZTSHUNT   (5)
  - The equivalent impedance (shunt) in transmission measurement.

AGENA_PARAMETER_CONVERSION_YTSHUNT   (6)
  - The equivalent admittance (shunt) in trasmission measurement.

AGENA_PARAMETER_CONVERSION_CONJUGATE (7)
  - The conjugate.

Default Value:
AGENA_PARAMETER_CONVERSION_ZREFLECT  (0)
     �    Selects the corresponding channel.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA E5061A/E5062A)

Default Value: 1
   �����  �    Status                           �� %  �  �    Instrument Handle                �/ > � �       State                            �� >� � x    Parameter                        �� > % � d    Channel                            	                Enable VI_TRUE Disable VI_FALSE              �Z Reflection AGENA_PARAMETER_CONVERSION_ZREFLECT Z Transmission AGENA_PARAMETER_CONVERSION_ZTRANSMIT Y Reflection AGENA_PARAMETER_CONVERSION_YREFLECT Y Transmission AGENA_PARAMETER_CONVERSION_YTRANSMIT Inverse S-parameter AGENA_PARAMETER_CONVERSION_INVERSION Z Trans Shunt AGENA_PARAMETER_CONVERSION_ZTSHUNT Y Trans Shunt AGENA_PARAMETER_CONVERSION_YTSHUNT Conjugate AGENA_PARAMETER_CONVERSION_CONJUGATE    1    7    This function configure handler IO control settings.
    S    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Port C Direction) out of range.
BFFC0003  Parameter 3 (Port D Direction) out of range.
BFFC0004  Parameter 4 (OUTPUT1/OUTPUT2 Setting) out of range.
BFFC0005  Parameter 5 (INDEX Signal Output) out of range.
BFFC0006  Parameter 6 (READY FOR TRIGGER Signal Output) out of range.
BFFC0007  Parameter 7 (Output) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Enables or disables outputting the INDEX signal to B6 of the handler I/O.

Valid Values:
VI_TRUE  (1) - Enable
VI_FALSE (0) - Disable

Default Value:
VI_FALSE (0)
     �    Sets the input/output direction of port C of the handler I/O.

Valid Values:
AGENA_IO_HANDLER_DIR_PORT_C_INPUT  (0) - Input
AGENA_IO_HANDLER_DIR_PORT_C_OUTPUT (1) - Output

Default Value:
AGENA_IO_HANDLER_DIR_PORT_C_INPUT (0)
     �    Sets the input/output direction of port D of the handler I/O.

Valid Values:
AGENA_IO_HANDLER_DIR_PORT_D_INPUT  (0) - Input
AGENA_IO_HANDLER_DIR_PORT_D_OUTPUT (1) - Output

Default Value:
AGENA_IO_HANDLER_DIR_PORT_D_INPUT (0)
     �    Sets HIGH/LOW of selected output of the handler I/O.

Valid Values:
AGENA_HANDLER_IO_OUTPUT_HIGH (0) - High
AGENA_HANDLER_IO_OUTPUT_LOW  (1) - Low

Default Value:
AGENA_HANDLER_IO_OUTPUT_HIGH (0)
     �    Enables or disables outputting the READY FOR TRIGGER signal to B7 of the handler I/O.

Valid Values:
VI_TRUE  (1) - Enable
VI_FALSE (0) - Disable

Default Value:
VI_FALSE (0)
     @    Selects output number.

Valid Range:
1 to 2

Default Value:
1
   �|����  �    Status                           �� %  �  �    Instrument Handle                �v � < �       INDEX Signal Output              �# > % � d    Port C Direction                 � > � � d    Port D Direction                 �� >� � d    OUTPUT1/OUTPUT2 Setting          �� � � �       READY FOR TRIGGER Signal Output  �� �� �  d    Output                             	                Enable VI_TRUE Disable VI_FALSE               RInput AGENA_IO_HANDLER_DIR_PORT_C_INPUT Output AGENA_IO_HANDLER_DIR_PORT_C_OUTPUT               RInput AGENA_IO_HANDLER_DIR_PORT_D_INPUT Output AGENA_IO_HANDLER_DIR_PORT_D_OUTPUT               BHigh AGENA_HANDLER_IO_OUTPUT_HIGH Low AGENA_HANDLER_IO_OUTPUT_LOW     Enable VI_TRUE Disable VI_FALSE    1    t    This function configure controlling of E5091A.

Notes:

(1) This function is not available for ENA E5061A/E5062A.
    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Multiplexer) out of range.
BFFC0004  Parameter 4 (State) out of range.
BFFC0005  Parameter 5 (Port 1) out of range.
BFFC0006  Parameter 6 (Port 2) out of range.
BFFC0007  Parameter 7 (Port 3) out of range.
BFFC0008  Parameter 8 (Port 4) out of range.
BFFC0009  Parameter 9 (Property Display) out of range.
BFFC0010  Parameter 10 (Control Lines) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Enables or disables the property display (the state of the port assignment) of the E5091A whose ID is specified by Multiplexer control.

Valid Values:
VI_TRUE  (1) - Enable
VI_FALSE (0) - Disable

Default Value:
VI_FALSE (0)
        Selects a port assigned to Port 1 of the E5091A whose ID is specified by Multiplexer control when measuring selected channel  in the measurement using the E5091A.

Valid Values:
AGENA_CONTROL_E5091A_PORT1_A  (0)
AGENA_CONTROL_E5091A_PORT1_T1 (1)

Default Value:
AGENA_CONTROL_E5091A_PORT1_A (0)

Notes:
If the port assigned to Port 2 is AGENA_CONTROL_E5091A_PORT2_T1 and you select AGENA_CONTROL_E5091A_PORT1_T1 as the port assigned to Port 1, the port assigned to Port 2 is changed to AGENA_CONTROL_E5091A_PORT2_T2 automatically.        Selects a port assigned to Port 2 of the E5091A whose ID is specified by Multiplexer control when measuring selected channel  in the measurement using the E5091A.

Valid Values:
AGENA_CONTROL_E5091A_PORT2_T1 (0)
AGENA_CONTROL_E5091A_PORT2_T2 (1)

Default Value:
AGENA_CONTROL_E5091A_PORT2_T1 (0)

Notes:
If the port assigned to Port 1 is AGENA_CONTROL_E5091A_PORT1_T1 and you select AGENA_CONTROL_E5091A_PORT2_T1 as the port assigned to Port 2, the port assigned to Port 1 is changed to AGENA_CONTROL_E5091A_PORT1_A automatically.    ^    Selects a port assigned to Port 3 of the E5091A whose ID is specified by Multiplexer control when measuring selected channel  in the measurement using the E5091A.

Valid Values:
AGENA_CONTROL_E5091A_PORT3_R1 (0) - R1+
AGENA_CONTROL_E5091A_PORT3_R2 (1) - R2+
AGENA_CONTROL_E5091A_PORT3_R3 (2) - R3+

Default Value:
AGENA_CONTROL_E5091A_PORT3_R1 (0)
    ^    Selects a port assigned to Port 4 of the E5091A whose ID is specified by Multiplexer control when measuring selected channel  in the measurement using the E5091A.

Valid Values:
AGENA_CONTROL_E5091A_PORT4_R1 (0) - R1-
AGENA_CONTROL_E5091A_PORT4_R2 (1) - R2-
AGENA_CONTROL_E5091A_PORT4_R3 (2) - R3-

Default Value:
AGENA_CONTROL_E5091A_PORT4_R1 (0)
     M    Selects the corresponding channel.

Valid Range: 1 to 16

Default Value: 1
        Enables or disables the control (switching the internal switch that connects between the ports and changing control line output) of the E5091A whose ID is specified by Multiplexer control.

Valid Values:
VI_TRUE  (1) - Enable
VI_FALSE (0) - Disable

Default Value:
VI_FALSE (0)
     P    Selects the corresponding multiplexer.

Valid Range: 1 to 2

Default Value: 1
    �    Sets the HIGH/LOW of all the control line of the E5091A whose ID is specified by Multiplexer control when measuring selected channel in the measurement using the E5091A.
To set the control lines, use values obtained by converting 8-bit binary values expressed by HIGH (1)/LOW (0) of individual lines to decimal values, assuming line 1 as LSB and line 8 as MSB.

Valid Range:
0 to 255

Default Value:
0
   �\����  �    Status                           �
 %  �  �    Instrument Handle                �� � � �       Property Display                 �� �   � d    Port 1                           �� � � � d    Port 2                           �� �. � d    Port 3                           �2 �� � d    Port 4                           �� >   �  d    Channel                          �� >. �       State                            � > � �  d    Multiplexer                      �e �. 	�  d    Control Lines                      	                Enable VI_TRUE Disable VI_FALSE               @A AGENA_CONTROL_E5091A_PORT1_A T1 AGENA_CONTROL_E5091A_PORT1_T1               BT1 AGENA_CONTROL_E5091A_PORT2_T1 T2 AGENA_CONTROL_E5091A_PORT2_T2               cR1 AGENA_CONTROL_E5091A_PORT3_R1 R2 AGENA_CONTROL_E5091A_PORT3_R2 R3 AGENA_CONTROL_E5091A_PORT3_R3               cR1 AGENA_CONTROL_E5091A_PORT4_R1 R2 AGENA_CONTROL_E5091A_PORT4_R2 R3 AGENA_CONTROL_E5091A_PORT4_R3    1     Enable VI_TRUE Disable VI_FALSE    1    0    %    This function setup date and time.
    3    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Display Clock) out of range.
BFFC0003  Parameter 3 (Year) out of range.
BFFC0004  Parameter 4 (Month) out of range.
BFFC0005  Parameter 5 (Day) out of range.
BFFC0006  Parameter 6 (Hour) out of range.
BFFC0007  Parameter 7 (Minute) out of range.
BFFC0008  Parameter 8 (Second) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Enables or disables the clock display at the right edge of the instrument status bar (at the bottom of the LCD display).

Valid Values:
VI_TRUE  (1) - Enable
VI_FALSE (0) - Disable

Default Value:
VI_TRUE (1)
     r    Sets the year of date of the clock built in the E5070B/E5071B.

Valid Range:
1980 to 2099

Default Value:
2005

     j    Sets the month of date of the clock built in the E5070B/E5071B.

Valid Range:
1 to 12

Default Value:
1
     h    Sets the day of date of the clock built in the E5070B/E5071B.

Valid Range:
1 to 31

Default Value:
1
     a    Sets the time of the clock built in the E5070B/E5071B.

Valid Range:
0 to 23

Default Value:
0
     a    Sets the time of the clock built in the E5070B/E5071B.

Valid Range:
0 to 59

Default Value:
0
     a    Sets the time of the clock built in the E5070B/E5071B.

Valid Range:
0 to 59

Default Value:
0
   �^����  �    Status                           ə %  �  �    Instrument Handle                �8 > > �       Display Clock                    � � % �  d    Year                             ˍ � � �  d    Month                            �� �� �  d    Day                              �o � % �  d    Hour                             �� � � �  d    Minute                           �A �� �  d    Second                             	               Enable VI_TRUE Disable VI_FALSE    2005    1    1    0    0    0    w    This function configure external signal generator.

Notes:

(1) This function is not available for ENA E5061A/E5062A.    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (GPIB Address) out of range.
BFFC0003  Parameter 3 (Type) out of range.
BFFC0008  Parameter 8 (Waiting Time) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     `    Sets the GPIB address of the external signal source.

Valid Range:
0 to 30

Default Value:
19
     V    Sets the type of the external signal source.

Valid Range:
1 to 3

Default Value:
3
    H    Sets the command string of the output frequency setting of the external signal source.

Default Value:
"FR %f% HZ"

Notes:
This value is available when Type control is set to 1 (User-defined). If another type of external signal source is selected, the selected external signal source command is used and this value is ignored.    E    Sets the command string of the power level setting of the external signal source. 

Default Value:
"AP %P% DM"

Notes:
This value is available when Type control is set to 1 (User-defined). If another type of external signal source is selected, the selected external signal source command is used and this value is ignored.
    (    Sets the preset command string for the external signal source.

Default Value:
""

Notes:
This value is available when Type control is set to 1 (User-defined). If another type of external signal source is selected, the selected external signal source command is used and this value is ignored.
    5    Sets the command string of the RF output on of the external signal source.

Default Value:
"R3"

Notes:
This value is available when Type control is set to 1 (User-defined). If another type of external signal source is selected, the selected external signal source command is used and this value is ignored.     �    Sets a wait time after setting the output frequency and the power level of the external signal source.

Valid Range:
0.0 to 1.0

Default Value:
0.1
   �Z����  �    Status                           �� %  �  �    Instrument Handle                Ջ >  �  d    GPIB Address                     �� > � �  d    Type                             �Q > �  �    Frequency Setting Command        ס v �  �    Power Level Setting Command      �� � �  �    Preset Command                   � � �  �    RF Power ON Command              �[ �� �  d    Waiting Time                       	               19    3    "FR %f% HZ"    "AP %P% DM"    ""    "R3"    0.1    r    This function configure initial source port.

Notes:

(1) This function is not available for ENA E5061A/E5062A.
    P    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (State) out of range.
BFFC0003  Parameter 3 (Port) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Enables or disables the Initial Source Port Control feature (to switch the stimulus output in the trigger hold state to a test port).

Valid Values:
VI_TRUE  (1) - Enable
VI_FALSE (0) - Disable

Default Value:
VI_TRUE (1)
     �    Specifies a test port to be selected for stimulus destination when the Initial Source Port Control feature is enabled.

Valid Range:
1 to 4

Default Value:
1
   ޞ����  �    Status                           �� %  �  �    Instrument Handle                � > > �  `    State                            �} > � �  d    Port                               	               Enable VI_TRUE Disable VI_FALSE    1    x    This function configure correction and temperature.

Notes:

(1) This function is not available for ENA E5061A/E5062A.    s    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (System Error Correction) out of range.
BFFC0003  Parameter 3 (High Temperature Mode) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Enables or disables the system error correction. Changing this state clears the calibration coefficients.

Valid Values:
VI_TRUE  (1) - Enable
VI_FALSE (0) - Disable

Default Value:
VI_TRUE (1)

     �    Enables or disables the high temperature measurement mode.

Valid Values:
VI_TRUE  (1) - Enable
VI_FALSE (0) - Disable

Default Value:
VI_FALSE (0)
   �����  �    Status                           �, %  �  �    Instrument Handle                �� > > �  `    System Error Correction          � > � �  `    High Temperature Mode              	               Enable VI_TRUE Disable VI_FALSE     Enable VI_TRUE Disable VI_FALSE    �    This function clears the measurement data used for averaging of selected channel. Measurement data before the execution of this command is not used for averaging.
    (    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Selects the corresponding channel.

Valid Range: 1 to 16     (for ENA E5070B/E5071B)
             1 to 4      (for ENA E5061A/E5062A)

Default Value: 1
   �����  �    Status                           �= %  �  �    Instrument Handle                �� > % �  d    Channel                            	               1    }    For the active trace of selected channel, copies the measurement data at the execution of the command to the memory trace.
    (    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Selects the corresponding channel.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA E5061A/E5062A)

Default Value: 1
   ������  �    Status                           �� %  �  �    Instrument Handle                �� > % �  d    Channel                            	               1    �    For selected trace of selected channel, executes the auto scale (function to automatically adjust the value of the reference graticule line and the scale per division to display the trace appropriately).
    T    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Trace) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     M    Selects the corresponding channel.

Valid Range: 1 to 16

Default Value: 1
     c    Selects the corresponding trace for scale configuration.

Valid Range: 1 to 16

Default Value: 1
   ������  �    Status                            %  �  �    Instrument Handle                � > % �  d    Channel                            > � �  d    Trace                              	               1    1    g    This function resets the calibration kit selected for selected channel to the factory setting state.
    (    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Selects the corresponding channel.

Valid Range: 1 to 16     (for ENA E5070B/E5071B)
             1 to 4      (for ENA E5061A/E5062A)

Default Value: 1
   �����  �    Status                           � %  �  �    Instrument Handle                � > % �  d    Channel                            	               1    �    For selected channel, measures the calibration data of the open, short, load, thru standard or isolation of the specified ports.
    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Standard) out of range.
BFFC0004  Parameter 4 (Port 1 (Response)) out of range.
BFFC0005  Parameter 5 (Port 2 (Stimulus)) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Selects the corresponding channel.

Valid Range: 1 to 16     (for ENA E5070B/E5071B)
             1 to 4      (for ENA E5061A/E5062A)

Default Value: 1
     I    Sets the specified port number.

Valid Range:
1 to 4

Default Value:
1
     �    Sets the specified port number.

Valid Range:
1 to 4

Default Value:
1

Notes:
Applies only for thru and isolation measurement, otherwise 
ignored.    �    Selects measure standard.

Valid Values:
AGENA_MEASURE_CAL_DATA_STANDARD_OPEN      (0) - Open standard
AGENA_MEASURE_CAL_DATA_STANDARD_SHORT     (1) - Short standard
AGENA_MEASURE_CAL_DATA_STANDARD_LOAD      (2) - Load standard
AGENA_MEASURE_CAL_DATA_STANDARD_THRU      (3) - Thru standard
AGENA_MEASURE_CAL_DATA_STANDARD_ISOLATION (4) - Isolation

Default Value:
AGENA_MEASURE_CAL_DATA_STANDARD_OPEN      (0)
   
x����  �    Status                           G %  �  �    Instrument Handle                � > % �  d    Channel                          � >) �  d    Port 1 (Response)                � >� �  d    Port 2 (Stimulus)                v > � � d    Standard                           	               1    1    1               �Open AGENA_MEASURE_CAL_DATA_STANDARD_OPEN Short AGENA_MEASURE_CAL_DATA_STANDARD_SHORT Load AGENA_MEASURE_CAL_DATA_STANDARD_LOAD Thru AGENA_MEASURE_CAL_DATA_STANDARD_THRU Isolation AGENA_MEASURE_CAL_DATA_STANDARD_ISOLATION   �    From the measured calibration data, calculates the calibration coefficients depending on the selected calibration type.
Calculating the calibration coefficients clears all calibration data whether or not used for the calculation and also clears the calibration type selections.

Notes:
If you execute this function before all necessary calibration data for calculating the calibration coefficients is measured, an error occurs and the function is ignored.
    (    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Selects the corresponding channel.

Valid Range: 1 to 16     (for ENA E5070B/E5071B)
             1 to 4      (for ENA E5061A/E5062A)

Default Value: 1
   6����  �    Status                           f %  �  �    Instrument Handle                 > % �  d    Channel                            	               1    �    Clears the error coefficient or the measurement value of the Mechanical Cal kit for calibration when the frequency offset mode is disabled for selected channel.
    T    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Clear) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Selects the corresponding channel.

Valid Range: 1 to 16     (for ENA E5070B/E5071B)
             1 to 4      (for ENA E5061A/E5062A)

Default Value: 1
        Selects between the error coefficient and the measurement value of the Mechanical Cal kit for calibration.

Valid Values:
AGENA_CALIBRATION_DATA_CLEAR_COEFFICIENT (0)
AGENA_CALIBRATION_DATA_CLEAR_DATA        (1)

Default Value:
AGENA_CALIBRATION_DATA_CLEAR_COEFFICIENT (0)
   ����  �    Status                           "b %  �  �    Instrument Handle                # > % �  d    Channel                          #� > � � x    Clear                              	               1               uCalibration Coefficients AGENA_CALIBRATION_DATA_CLEAR_COEFFICIENT Calibration Data AGENA_CALIBRATION_DATA_CLEAR_DATA    �    Executes 1-port, full 2-port, full 3-port, full 4-port, response  calibration or the confidence check of the specified ports of selected channel using the ECal (Electrical Calibration) module.
    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Calibration) out of range.
BFFC0004  Parameter 4 (Port 1) out of range.
BFFC0005  Parameter 5 (Port 2) out of range.
BFFC0006  Parameter 6 (Port 3) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Selects the corresponding channel.

Valid Range: 1 to 16     (for ENA E5070B/E5071B)
             1 to 4      (for ENA E5061A/E5062A)

Default Value: 1
     �    Specifies port number.

Valid Range:
1 to 4

Default Value:
1

Notes:
Value is not used when Calibration is set to AGENA_CALIBRATION_EXECUTE_4_PORT or AGENA_CALIBRATION_EXECUTE_CONF_CHECK.     �    Specifies port number.

Valid Range:
1 to 4

Default Value:
2

Notes:
Value is not used when Calibration is set to AGENA_CALIBRATION_EXECUTE_1_PORT, GENA_CALIBRATION_EXECUTE_4_PORT or AGENA_CALIBRATION_EXECUTE_CONF_CHECK.    �    Selects calibration type for execution.

Valid Values:
AGENA_CALIBRATION_EXECUTE_1_PORT      (0) - 1-port
AGENA_CALIBRATION_EXECUTE_2_PORT      (1) - Full 2-port
AGENA_CALIBRATION_EXECUTE_3_PORT      (2) - Full 3-port
AGENA_CALIBRATION_EXECUTE_4_PORT      (3) - Full 4-port
AGENA_CALIBRATION_EXECUTE_RESPONSE    (4) - Response
AGENA_CALIBRATION_EXECUTE_CONF_CHECK  (5) - Confidence check
AGENA_CALIBRATION_EXECUTE_EN_RESPONSE (6) - Enhanced Response

Default Value:
AGENA_CALIBRATION_EXECUTE_1_PORT     (0)

Notes:

(1) ENA E5061A/E5062A don't support this values: Full 3-port, Full 4-port and Confidence check.

(2) Enhanced Response is available only for ENA E5061A/E5062A.
     �    Specifies port number.

Valid Range:
1 to 4

Default Value:
3

Notes:
Value is used when Calibration is set to AGENA_CALIBRATION_EXECUTE_3_PORT only.   &�����  �    Status                           +� %  �  �    Instrument Handle                ,~ > % �  d    Channel                          -  > �  d    Port 1                           -� >� �  d    Port 2                           .� > � � d    Calibration                      1{ �� �  d    Port 3                             	               1    1    2              I1-port AGENA_CALIBRATION_EXECUTE_1_PORT Full 2-port AGENA_CALIBRATION_EXECUTE_2_PORT Full 3-port AGENA_CALIBRATION_EXECUTE_3_PORT Full 4-port AGENA_CALIBRATION_EXECUTE_4_PORT Response AGENA_CALIBRATION_EXECUTE_RESPONSE Confidence Check AGENA_CALIBRATION_EXECUTE_CONF_CHECK Enhanced Response AGENA_CALIBRATION_EXECUTE_EN_RESPONSE    3       For selected port, measure the power calibration data using the specified power sensor. When the measurement is complete successfully, the power level error correction is automatically
enabled.

Notes:

(1) This function is not available for ENA E5061A/E5062A.    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Port) out of range.
BFFC0004  Parameter 4 (Sensor) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     M    Selects the corresponding channel.

Valid Range: 1 to 16

Default Value: 1
     �    Selects power sensor.

Valid Values:
AGENA_POWER_CALIBRATION_SENSOR_A (0) - Power sensor A
AGENA_POWER_CALIBRATION_SENSOR_B (1) - Power sensor B

Default Value:
AGENA_POWER_CALIBRATION_SENSOR_A (0)
     ?    Specifies port number.

Valid Range:
1 to 4

Default Value:
1   6����  �    Status                           :� %  �  �    Instrument Handle                ;> > % �  d    Channel                          ;� >� � d    Sensor                           <c > � �  d    Port                               	               1               `Power Sensor A AGENA_POWER_CALIBRATION_SENSOR_A Power Sensor B AGENA_POWER_CALIBRATION_SENSOR_B    1   ;    From the measured calibration data, calculates the error coefficient for the calibration type selected with agena_confScalarCal function.

After the error coefficient is calculated, the measured data and the calibration type setting are cleared.

Notes:

(1) This function is not available for ENA E5061A/E5062A.
    (    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     M    Selects the corresponding channel.

Valid Range: 1 to 16

Default Value: 1
   ?����  �    Status                           C� %  �  �    Instrument Handle                DN > % �  d    Channel                            	               1       Clears the error coefficient or the measurement value of the Mechanical Cal kit for calibration when the frequency offset mode is enabled for selected channel. This command also
clears the measurement value of the power meter.

To toggle the frequency offset mode, use agena_confFreqOffset function.

Notes:
(1) Settings that have been temporarily changed due to measurement for each standard (number of traces, measurement parameter, and so on) return to their original values.

(2) This function does not clear the error coefficient when the frequency offset mode is disabled.

(3) This function is not available for ENA E5061A/E5062A.    T    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Clear) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     M    Selects the corresponding channel.

Valid Range: 1 to 16

Default Value: 1
        Selects between the error coefficient and the measurement value of the Mechanical Cal kit for calibration.

Valid Values:
AGENA_CALIBRATION_DATA_CLEAR_COEFFICIENT (0)
AGENA_CALIBRATION_DATA_CLEAR_DATA        (1)

Default Value:
AGENA_CALIBRATION_DATA_CLEAR_COEFFICIENT (0)
   G�����  �    Status                           L: %  �  �    Instrument Handle                L� > % �  d    Channel                          M. > � � x    Clear                              	               1               uCalibration Coefficients AGENA_CALIBRATION_DATA_CLEAR_COEFFICIENT Calibration Data AGENA_CALIBRATION_DATA_CLEAR_DATA    �    For selected channel, measures the calibration data of the open, short, load, thru or power calibration standard of the specified port when the frequency offset mode is enabled.

Notes:

(1) This function is not available for ENA E5061A/E5062A.    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Standard) out of range.
BFFC0004  Parameter 4 (Sensor) out of range.
BFFC0005  Parameter 5 (Port 1 (Measurement)) out of range.
BFFC0006  Parameter 6 (Port 2 (Specified Freq)) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     M    Selects the corresponding channel.

Valid Range: 1 to 16

Default Value: 1
     K    Sets port number for measurement.

Valid Range:
1 to 4

Default Value:
1
     `    Sets port number for which the frequency is specified.

Valid Range:
1 to 4

Default Value:
1
    [    Selects measure scalar calibration data standard.

Valid Values:
AGENA_MEASURE_CAL_SCALAR_STANDARD_OPEN  (0)
AGENA_MEASURE_CAL_SCALAR_STANDARD_SHORT (1)
AGENA_MEASURE_CAL_SCALAR_STANDARD_LOAD  (2)
AGENA_MEASURE_CAL_SCALAR_STANDARD_THRU  (3)
AGENA_MEASURE_CAL_SCALAR_STANDARD_POWER (4)

Default Value:
AGENA_MEASURE_CAL_SCALAR_STANDARD_OPEN  (0)
        Specifies power sensor.

Valid Values:
AGENA_POWER_CALIBRATION_SENSOR_A (0) - Power sensor A
AGENA_POWER_CALIBRATION_SENSOR_B (1) - Power sensor B

Default Value:
AGENA_POWER_CALIBRATION_SENSOR_A (0)

Notes:
This control is valid only for power calibration standard.   P�����  �    Status                           U� %  �  �    Instrument Handle                VX > % �  d    Channel                          V� � % �  d    Port 1 (Measurement)             W  � � �  d    Port 2 (Specified Freq)          Wh > � � d    Standard                         X� >� � d    Sensor                             	               1    1    1               �Open AGENA_MEASURE_CAL_SCALAR_STANDARD_OPEN Short AGENA_MEASURE_CAL_SCALAR_STANDARD_SHORT Load AGENA_MEASURE_CAL_SCALAR_STANDARD_LOAD Thru AGENA_MEASURE_CAL_SCALAR_STANDARD_THRU Power Calibration AGENA_MEASURE_CAL_SCALAR_STANDARD_POWER               `Power Sensor A AGENA_POWER_CALIBRATION_SENSOR_A Power Sensor B AGENA_POWER_CALIBRATION_SENSOR_B    �    For selected channel, performs 1-port or 2-port ECal module measurement and error coefficient calculation (scalar-mixer calibration) when the frequency offset mode is enabled.

Notes:

(1) This function is not available for ENA E5061A/E5062A.
    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Calibration) out of range.
BFFC0004  Parameter 4 (Port 1) out of range.
BFFC0005  Parameter 5 (Port 2) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     M    Selects the corresponding channel.

Valid Range: 1 to 16

Default Value: 1
     ;    Sets port number.

Valid Range:
1 to 4

Default Value:
1
     f    Sets port number.

Valid Range:
1 to 4

Default Value:
1

Notes:
Valid for 2-port calibration only.
     �    Selects calibration method.

Valid Values:
AGENA_SCALAR_MIXER_CALIB_1_PORT (0)
  - 1-port scalar-mixer calibration

AGENA_SCALAR_MIXER_CALIB_2_PORT (1)
  - 2-port scalar-mixer calibration

Default Value:
AGENA_SCALAR_MIXER_CALIB_1_PORT (0)
   ]�����  �    Status                           b� %  �  �    Instrument Handle                c3 > % �  d    Channel                          c� >/ �  d    Port 1                           c� >� �  d    Port 2                           d9 > � � d    Calibration                        	               1    1    1               f1-port Calibration AGENA_SCALAR_MIXER_CALIB_1_PORT 2-port Calibration AGENA_SCALAR_MIXER_CALIB_2_PORT   �    For selected channel, calculates the receiver calibration error
coefficient for the specified port (executes receiver calibration).

The measurement port and the source port are THRU-connected for execution. Therefore, if the same port number is specified for the measurement port and the source port, an error occurs.

Because information of power calibration for both the measurement port and the source port is used for error coefficient calculation, the precision of receiver calibration is improved by executing power calibration for the both ports before executing receiver calibration.

Notes:

(1) This function is not available for ENA E5061A/E5062A.
    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Receiver) out of range.
BFFC0004  Parameter 4 (Port) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     M    Selects the corresponding channel.

Valid Range: 1 to 16

Default Value: 1
     f    Selects the corresponding receiver for receiver calibration.

Valid Range: 1 to 4

Default Value: 1
     ;    Sets port number.

Valid Range:
1 to 4

Default Value:
1
   i�����  �    Status                           n- %  �  �    Instrument Handle                n� > % �  d    Channel                          o! > � �  d    Receiver                         o� >� �  d    Port                               	               1    1    1        This function send trigger.
        This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Ignore Trigger Source) out of range.
BFFC0003  Parameter 3 (Wait For OPC) out of range.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Specifies if function ignore trigger source or not.

Valid Values:
VI_TRUE  (1) - On
VI_FALSE (0) - Off

Default Value:
VI_FALSE (0)
     ~    Specifies if function wait for OPC or not.

Valid Values:
VI_TRUE  (1) - On
VI_FALSE (0) - Off

Default Value:
VI_FALSE (0)
   q ����  �    Status                           u5 %  �  �    Instrument Handle                u� > p �       Ignore Trigger Source            vc > �       Wait For OPC                       	               On VI_TRUE Off VI_FALSE    On VI_TRUE Off VI_FALSE   �    Changes the state of each channel of selected channel to the startup state in the trigger system.

When this function is executed for a channel in the idle state, it goes into the initiate state immediately. Then, after measurement is executed once, it goes back to the idle state.

If this function is executed for a channel that is not in the idle state or for which the continuous initiation mode is enabled, an error occurs.
    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Selects the corresponding channel.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA D5061A/E5062A)

Default Value: 1
   y�����  �    Status                           }� %  �  �    Instrument Handle                ~- > % �  d    Channel                            	               1    �    This function aborts the measurement and changes the trigger sequence for all channels to idle state.

After the change to the idle state, the channels for which the continuous initiation mode is enabled change into the initiate state.
    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None   �w����  �    Status                           � %  �  �    Instrument Handle                  	               ;    This function resets the result of the average function.
    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

BFFC0002  Parameter 2 (Channel) out of range.

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Selects the corresponding channel.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA E5061A/E5062A)

Default Value: 1
   �x����  �    Status                           �L   �  �    Instrument Handle                �� R � �  d    Channel                            	               1    N    This function search marker and returns position and value of found marker.
    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
        0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Marker) out of range.
BFFC0004  Parameter 4 (Function) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None    �    For the active trace of selected channel, selects the search type of selected marker.

Valid Values:
AGENA_MARKER_SEARCH_MAXIMUM (0)
  - Specifies the maximum value search.

AGENA_MARKER_SEARCH_MINIMUM (1)
  - Specifies the minimum value search.

AGENA_MARKER_SEARCH_PEAK    (2)
  - Specifies the maximum positive (minimum negative) peak search.

AGENA_MARKER_SEARCH_LPEAK   (3)
  - Specifies the peak search to the left from the marker position.

AGENA_MARKER_SEARCH_RPEAK   (4)
  - Specifies the peak search to the right from the marker position.

AGENA_MARKER_SEARCH_TARGET  (5)
  - Specifies the search for the target closest to the current marker position.

AGENA_MARKER_SEARCH_LTARGET (6)
  - Specifies the target search to the left from the marker position.

AGENA_MARKER_SEARCH_RTARGET (7)
  - Specifies the target search to the right from the marker position.

Default Value:
AGENA_MARKER_SEARCH_PEAK (2)
     �    Selects the corresponding channel.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA E5061A/E5062B)

Default Value: 1
     �    Selects the corresponding marker.

Valid Range: 1 to 10
1 to 9 - marker1 to marker9
10     - reference marker

Default Value: 1
     [    For the active trace of selected channel, returns the stimulus value of selected marker.
     �    For the active trace of selected channel, reads out the response value of selected marker.

Notes:
When the reference marker mode is enabled, the readout value is the value relative to the reference marker.   ������  �    Status                           �E %  �  �    Instrument Handle                �� >� � d    Function                         �� > % � d    Channel                          �  > � � d    Marker                          ���� W M��                                          ��  % �  `    X Value                          �  � �  `    Y Value                            	                        "Maximum AGENA_MARKER_SEARCH_MAXIMUM Minimum AGENA_MARKER_SEARCH_MINIMUM Peak AGENA_MARKER_SEARCH_PEAK Left Peak AGENA_MARKER_SEARCH_LPEAK Right Peak AGENA_MARKER_SEARCH_RPEAK Target AGENA_MARKER_SEARCH_TARGET Left Target AGENA_MARKER_SEARCH_LTARGET Right Target AGENA_MARKER_SEARCH_RTARGET    1    1    7|---------------------- Result ----------------------|    	           	           �    For the active trace of selected channel, sets the value of the specified item to the value of the position of selected marker.
    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
        0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Marker) out of range.
BFFC0004  Parameter 4 (Marker To) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None    u    For the active trace of selected channel, sets the value of the specified item to the value of the position of selected marker.

Regardless of the enabled/disabled of the reference marker mode, the value when the reference marker mode is disabled is always set.

Valid Values:
AGENA_MARKER_SET_TO_START  (0)
  - Sets the sweep start value to the stimulus value at the marker position.

AGENA_MARKER_SET_TO_STOP   (1)
  - Sets the sweep stop value to the stimulus value at the marker position.

AGENA_MARKER_SET_TO_CENTER (2)
  - Sets the sweep center value to the stimulus value at the marker position.

AGENA_MARKER_SET_TO_RLEVEL (3)
  - Sets the reference line value to the response value at the marker position.

AGENA_MARKER_SET_TO_DELAY  (4)
  - Sets the electrical delay time value to the group delay value at the marker position.

Default Value:
AGENA_MARKER_SET_TO_START (0)
     �    Selects the corresponding channel.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA E5061A/E5062A)

Default Value: 1
     �    Selects the corresponding marker.

Valid Range: 1 to 10
1 to 9 - marker1 to marker9
10     - reference marker

Default Value: 1
   ������  �    Status                           �e %  �  �    Instrument Handle                � >� � d    Marker To                        �� > % � d    Channel                          �! > � � d    Marker                             	                          �Start Freq. AGENA_MARKER_SET_TO_START Stop Freq. AGENA_MARKER_SET_TO_STOP Center Freq. AGENA_MARKER_SET_TO_CENTER Reference AGENA_MARKER_SET_TO_RLEVEL Electrical Delay AGENA_MARKER_SET_TO_DELAY    1    1    r    For the active trace of selected channel, executes the analysis specified with the agena_confAnalysis function.
    L    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
        0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Selects the corresponding channel.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA E5061A/E5062A)

Default Value: 1
   �����  �    Status                           �m %  �  �    Instrument Handle                � > % � d    Channel                            	               1    �    For the active trace of selected channel, changes the frequency range to match with the low-pass type transformation of the transformation function of the time domain function.
    L    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
        0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Selects the corresponding channel.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA E5061A/E5062A)

Default Value: 1
   �����  �    Status                           �o %  �  �    Instrument Handle                � > % � d    Channel                            	               1    )    This function configure file handling.
    e    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Items) out of range.
BFFC0003  Parameter 3 (Store All Channels/Traces) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None    q    Selects the contents saved when saving the instrument state into a file.

Valid Values:
AGENA_FILE_HANDLING_ITEM_STATE   (0)
  - Specifies the save of the measurement conditions only.

AGENA_FILE_HANDLING_ITEM_CSTATE  (1)
  - Specifies the save of the measurement confitions and the calibration state.

AGENA_FILE_HANDLING_ITEM_DSTATE  (2)
  - Specifies the save of the measurement conditions and the formatted data array.

AGENA_FILE_HANDLING_ITEM_CDSTATE (3)
  - Specifies the save of the measurement conditions and the calibration state, and the formatted data array.

Default Value:
AGENA_FILE_HANDLING_ITEM_CSTATE (1)
        Selects whether to save the setting of all channels/traces or that of the displayed channels/traces only as the instrument state to be saved.

Valid Values:
VI_TRUE  (1) - All channels/traces
VI_FALSE (0) - Displayed channels/traces only

Default Value:
VI_FALSE (0)
   ������  �    Status                           �  %  �  �    Instrument Handle                �� > % � d    Items                            � > � �       Store All Channels/Traces          	                         �State AGENA_FILE_HANDLING_ITEM_STATE CState AGENA_FILE_HANDLING_ITEM_CSTATE DState AGENA_FILE_HANDLING_ITEM_DSTATE CDState AGENA_FILE_HANDLING_ITEM_CDSTATE    All VI_TRUE Displayed VI_FALSE    =    This function saves specified instrument data into a file.
    N    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
        0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Data Type) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None    c    Selects the data type which will be store.

Valid Values:
AGENA_FILE_DATA_TYPE_INSTR_STATE     (0)
AGENA_FILE_DATA_TYPE_FORMATTED       (1)
AGENA_FILE_DATA_TYPE_IMAGE           (2)
AGENA_FILE_DATA_TYPE_SEG_SWEEP_TABLE (3)
AGENA_FILE_DATA_TYPE_LIMIT_TABLE     (4)
AGENA_FILE_DATA_TYPE_POWER_SENS_A    (5)
AGENA_FILE_DATA_TYPE_POWER_SENS_B    (6)
AGENA_FILE_DATA_TYPE_VBA_PROJECT     (7)
AGENA_FILE_DATA_TYPE_LOSS_COM_1      (8)
AGENA_FILE_DATA_TYPE_LOSS_COM_2      (9)
AGENA_FILE_DATA_TYPE_LOSS_COM_3      (10)
AGENA_FILE_DATA_TYPE_LOSS_COM_4      (11)

Default Value:
AGENA_FILE_DATA_TYPE_INSTR_STATE  (0)

Notes:
(1) ENA E5061A/E5062A don't support this values: AGENA_FILE_DATA_TYPE_POWER_SENS_A , AGENA_FILE_DATA_TYPE_POWER_SENS_B,
AGENA_FILE_DATA_TYPE_LOSS_COM_1, AGENA_FILE_DATA_TYPE_LOSS_COM_2, AGENA_FILE_DATA_TYPE_LOSS_COM_3,
AGENA_FILE_DATA_TYPE_LOSS_COM_4
    �    Specify the file name with the .sta extension. If you want to specify a file on the floppy disk drive, you need to add "A:" at the beginning of the file name. When you use directory names and file name, separate them with "/" (slash) or "\" (backslash).

Notes:
(1) If a file with the specified file name exists, its contents are overwritten.

(2) Size of file name must be 254 characters or less.   �#����  �    Status                           �y %  �  �    Instrument Handle                � > % � �    Data Type                        ǃ > � �  d    File Name                          	                         ~Entire Instrument State AGENA_FILE_DATA_TYPE_INSTR_STATE Formatted Data Array AGENA_FILE_DATA_TYPE_FORMATTED Image on the LCD display AGENA_FILE_DATA_TYPE_IMAGE Segment Sweep Table AGENA_FILE_DATA_TYPE_SEG_SWEEP_TABLE Limit Table AGENA_FILE_DATA_TYPE_LIMIT_TABLE Power Sensor A AGENA_FILE_DATA_TYPE_POWER_SENS_A Power Sensor B AGENA_FILE_DATA_TYPE_POWER_SENS_B VBA Project AGENA_FILE_DATA_TYPE_VBA_PROJECT Loss Compensation Table 1 AGENA_FILE_DATA_TYPE_LOSS_COM_1 Loss Compensation Table 2 AGENA_FILE_DATA_TYPE_LOSS_COM_2 Loss Compensation Table 3 AGENA_FILE_DATA_TYPE_LOSS_COM_3 Loss Compensation Table 4 AGENA_FILE_DATA_TYPE_LOSS_COM_4    ""    ?    This function recalls specified instrument data into a file.
    N    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
        0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Data Type) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None    =    Specify the file name with the .sta extension. If you want to specify a file on the floppy disk drive, you need to add "A:" at the beginning of the file name. When you use directory names and file name, separate them with "/" (slash) or "\" (backslash).

Notes:
(1) Size of file name must be 254 characters or less.        Selects the data type which will be store.

Valid Values:
AGENA_FILE_DATA_TYPE_INSTR_STATE     (0)
AGENA_FILE_DATA_TYPE_SEG_SWEEP_TABLE (3)
AGENA_FILE_DATA_TYPE_LIMIT_TABLE     (4)
AGENA_FILE_DATA_TYPE_POWER_SENS_A    (5)
AGENA_FILE_DATA_TYPE_POWER_SENS_B    (6)
AGENA_FILE_DATA_TYPE_VBA_PROJECT     (7)
AGENA_FILE_DATA_TYPE_LOSS_COM_1      (8)
AGENA_FILE_DATA_TYPE_LOSS_COM_2      (9)
AGENA_FILE_DATA_TYPE_LOSS_COM_3      (10)
AGENA_FILE_DATA_TYPE_LOSS_COM_4      (11)

Default Value:
AGENA_FILE_DATA_TYPE_INSTR_STATE  (0)

Notes:
(1) ENA E5061A/E5062A don't support this values: AGENA_FILE_DATA_TYPE_POWER_SENS_A , AGENA_FILE_DATA_TYPE_POWER_SENS_B,
AGENA_FILE_DATA_TYPE_LOSS_COM_1, AGENA_FILE_DATA_TYPE_LOSS_COM_2, AGENA_FILE_DATA_TYPE_LOSS_COM_3,
AGENA_FILE_DATA_TYPE_LOSS_COM_4
   ������  �    Status                           �. %  �  �    Instrument Handle                �� > � �  d    File Name                        � > % � �    Data Type                          	               ""            
  Entire Instrument State AGENA_FILE_DATA_TYPE_INSTR_STATE Segment Sweep Table AGENA_FILE_DATA_TYPE_SEG_SWEEP_TABLE Limit Table AGENA_FILE_DATA_TYPE_LIMIT_TABLE Power Sensor A AGENA_FILE_DATA_TYPE_POWER_SENS_A Power Sensor B AGENA_FILE_DATA_TYPE_POWER_SENS_B VBA Project AGENA_FILE_DATA_TYPE_VBA_PROJECT Loss Compensation Table 1 AGENA_FILE_DATA_TYPE_LOSS_COM_1 Loss Compensation Table 2 AGENA_FILE_DATA_TYPE_LOSS_COM_2 Loss Compensation Table 3 AGENA_FILE_DATA_TYPE_LOSS_COM_3 Loss Compensation Table 4 AGENA_FILE_DATA_TYPE_LOSS_COM_4       Saves the instrument state of the items set for the active channel specific to that channel only into the specified register (volatile memory).

Notes:
Notice that, if an instrument state has been saved already in the specified register, its contents are overwritten.
    T    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
        0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Memory Register) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Specifies register (volatile memory).

Valid Values:
AGENA_MEMORY_REGISTER_A (0)
AGENA_MEMORY_REGISTER_B (1)
AGENA_MEMORY_REGISTER_C (2)
AGENA_MEMORY_REGISTER_D (3)

Default Value:
AGENA_MEMORY_REGISTER_A (0)
   �P����  �    Status                           ެ %  �  �    Instrument Handle                �K > 9 � d    Memory Register                    	                          hA AGENA_MEMORY_REGISTER_A B AGENA_MEMORY_REGISTER_B C AGENA_MEMORY_REGISTER_C D AGENA_MEMORY_REGISTER_D       Saves the calibration coefficient of the active channel into the specified register.

Notes:
(1) Notice that, if an instrument state has been saved already in the specified register, its contents are overwritten.

(2) This function is available only for ENA E5061A/E5062A.
    T    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
        0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Memory Register) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Specifies register (volatile memory).

Valid Values:
AGENA_MEMORY_REGISTER_A (0)
AGENA_MEMORY_REGISTER_B (1)
AGENA_MEMORY_REGISTER_C (2)
AGENA_MEMORY_REGISTER_D (3)

Default Value:
AGENA_MEMORY_REGISTER_A (0)
   �g����  �    Status                           ��   �  �    Instrument Handle                �b 3 ( � d    Memory Register                    	                          hA AGENA_MEMORY_REGISTER_A B AGENA_MEMORY_REGISTER_B C AGENA_MEMORY_REGISTER_C D AGENA_MEMORY_REGISTER_D    �    Recalls the instrument state for an individual channel from the specified register as the setting of the active channel.

Notes:
It is possible to recall the register from a different channel where it was saved.
    T    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
        0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Memory Register) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Specifies register (volatile memory).

Valid Values:
AGENA_MEMORY_REGISTER_A (0)
AGENA_MEMORY_REGISTER_B (1)
AGENA_MEMORY_REGISTER_C (2)
AGENA_MEMORY_REGISTER_D (3)

Default Value:
AGENA_MEMORY_REGISTER_A (0)
   �A����  �    Status                           � %  �  �    Instrument Handle                �< > % � d    Memory Register                    	                          hA AGENA_MEMORY_REGISTER_A B AGENA_MEMORY_REGISTER_B C AGENA_MEMORY_REGISTER_C D AGENA_MEMORY_REGISTER_D       Recalls the calibration coefficient for an individual channel from the specified register as the setting of the active channel.

Notes:
(1) It is possible to recall the register from a different channel where it was saved.

(2) This function is available only for ENA E5061A/E5062A.
    T    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
        0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Memory Register) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Specifies register (volatile memory).

Valid Values:
AGENA_MEMORY_REGISTER_A (0)
AGENA_MEMORY_REGISTER_B (1)
AGENA_MEMORY_REGISTER_C (2)
AGENA_MEMORY_REGISTER_D (3)

Default Value:
AGENA_MEMORY_REGISTER_A (0)
   �b|���  �    Status                           ��   �  �    Instrument Handle                �] 3  � d    Memory Register                    	                          hA AGENA_MEMORY_REGISTER_A B AGENA_MEMORY_REGISTER_B C AGENA_MEMORY_REGISTER_C D AGENA_MEMORY_REGISTER_D    F    Deletes the instrument state for each channel in all the registers.
        This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
        0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None   ������  �    Status                           �� %  �  �    Instrument Handle                  	               =    This function creates, deletes directory or copies a file.
    N    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
        0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Operation) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Specifies operation.

Valid Values:
AGENA_FILE_MANAGER_CREATE_DIR (0)
AGENA_FILE_MANAGER_COPY_FILE  (1)
AGENA_FILE_MANAGER_DELETE_DIR (2)

Default Value:
AGENA_FILE_MANAGER_CREATE_DIR (0)
     �    Directory name for create or delete directory or source file name for copy.

Notes:
Number of characters in string must be 254 characters or less.
     �    Destination file name for copy.

Notes:
(1) Number of characters in string must be 254 characters or less.

(2) This value is valid for copy file only.

   �/����  �    Status                           � %  �  �    Instrument Handle                $ > % � d    Operation                        � > � �  d    Source                           � >� �  d    Destination                        	                          �Create Directory AGENA_FILE_MANAGER_CREATE_DIR Copy File AGENA_FILE_MANAGER_COPY_FILE Delete Directory AGENA_FILE_MANAGER_DELETE_DIR    ""    ""   �    Writes data to a file on the built-in storage device of the E5070B/E5071B.

By reading out data with this function and writing it to a file on the external controller, file transfer from the E5070B/E5071B to the external controller can be realized. On the other hand, by reading out data from the external controller and writing it to a file on the E5070B/E5071B with this function, file transfer from the external controller to the E5070B/E5071B can be realized.

Specify the file name with the extension. If you want to specify a file on the floppy disk drive, you need to add "A:" at the beginning of the file name. When you use directory names and file name, separate them with "/" (slash) or "\" (backslash).
        This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
        0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     ^    Specifies file name.

Notes:
Number of characters in string must be 254 characters or less.
     &    Specifies size of Data Block Array.
     4    Data block which will be written into instrument.
   
�����  �    Status                           � %  �  �    Instrument Handle                { > % �  d    File Name                        � > � �  d    Data Block Size                   >� �  d    Data Block Array                   	               ""    0       �    Reads data from a file on the built-in storage device of the E5070B/E5071B.

By reading out data with this function and writing it to a file on the external controller, file transfer from the E5070B/E5071B to the external controller can be realized. On the other hand, by reading out data from the external controller and writing it to a file on the E5070B/E5071B with this funcition, file transfer from the external controller to the E5070B/E5071B can be realized.

Specify the file name with the extension. If you want to specify 
a file on the floppy disk
drive, you need to add "A:" at the beginning of the file name. When you use directory names and file name, separate them with "/" (slash) or "\" (backslash).
        This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
        0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     #    Allocated buffer for data block.
     ^    Specifies file name.

Notes:
Number of characters in string must be 254 characters or less.
     6    Number of bytes allocated in buffer for data block.
     0    Returns number of bytes read from instrument.
   J����  �    Status                           o %  �  �    Instrument Handle                 >� �  `    Data Block                       9 > % �  d    File Name                        � > � �  d    Buffer Size                      � � % �  d    Bytes Read                         	               	            ""    0    	           �    This function reads out the following information on the built-in storage device of the E5070B/E5071B.

To read out the information in the root directory (folder), specify "\" (backslash). If you want to specify a directory on the floppy disk drive, you need to add "A:" at the beginning of the file name. Separate directory names with "/" (slash) or "\" (backslash).

- Space in use
- Available space
- Name and size of all files (including directories) in the specified directory.
        This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
        0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None         Specifies directory.

To read out the information in the root directory (folder), specify "\" (backslash). If you want to specify a directory on the floppy disk drive, you need to add "A:" at the beginning of the file name. Separate directory names with "/" (slash) or "\" (backslash).
     �    Rest of response string.

String format:
{Name 1},,{Size 1},...,{Name N},,{Size N}

Where:
{Name n}
   - Name of the n-th file (directory).

{Size n}
   - Size (byte) of the n-th file (directory). Always 0 for directories.
     6    Space in use of the built-in storage device (byte).
     9    Available space of the built-in storage device (byte).
     :    Specifies nubmer of bytes allocated in contents buffer.
   s����  �    Status                           !� %  �  �    Instrument Handle                "7 > % �  d    Directory                        #_ � � �  d    Contents                         $H > � �  d    Used Size                        $� >� �  d    Free Space                       $� � % �  d    Buffer Size                        	               ""    	            	           	           0    �    This function outputs the display image on the LCD display to the printer connected to the E5070B/E5071B or abort the print operation.
    N    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
        0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Operation) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None        Selects operation for hardcopy.

Valid Value:
AGENA_HARDCOPY_EXECUTE (0)
  - Outputs the display image on the LCD display to the printer connected to the E5070B/E5071B.

AGENA_HARDCOPY_ABORT   (1)
  - Aborts the print output.

Default Value:
AGENA_HARDCOPY_ABORT   (1)
   'L����  �    Status                           +� %  �  �    Instrument Handle                ,A > % � d    Operation                          	                         :Execute AGENA_HARDCOPY_EXECUTE Abort AGENA_HARDCOPY_ABORT    +    This function reads system informations.
        This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
        0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     L    Reads out the upper limit of the number of channels of the E5070B/E5071B.
     A    Reads out the upper limit of the number of traces per channel.
     6    Reads out the number of ports of the E5070B/E5071B.
     �    Reads out the system spec version of the E5070B/E5071B.

1 means applying new system specifications.
0 means applying old system specifications.
   .�����  �    Status                           2� %  �  �    Instrument Handle                3G > % �  d    Number of Channels               3� > � �  d    Number of Traces                 3� >� �  d    Number of Ports                  4" � % �  d    System Version                     	               	            	            	            	                Turns OFF the E5070B/E5071B.
        This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
        0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None   6b����  �    Status                           :� %  �  �    Instrument Handle                  	               ^    Sets the security level.

Notes:

(1) This function is available only for ENA E5061A/E5062A.    N    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
        0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Operation) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None    U    Selects the security level.

Valid Value:
AGENA_SECURITY_LEVEL_NONE (0)
  - Turns OFF the security level.

AGENA_SECURITY_LEVEL_LOW   (1)
  - Turns ON and specifies LOW level to the security level.

AGENA_SECURITY_LEVEL_HIGH  (2)
  - Turns ON and specifies HIGH level to the security level.

Default Value:
AGENA_SECURITY_LEVEL_NONE   (0)
   <����  �    Status                           @\   �  �    Instrument Handle                @� 4 / � d    Security Level                     	                          YOff AGENA_SECURITY_LEVEL_OFF Low AGENA_SECURITY_LEVEL_LOW High AGENA_SECURITY_LEVEL_HIGH    �    This function reads out whether warm-up to satisfy the specifications of the E5070B/E5071B is enough.

Notes:

(1) This function is not available for ENA E5061A/E5062A.        This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
        0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Reads out whether warm-up to satisfy the specifications of the E5070B/E5071B is enough.

Returned Values:
VI_TRUE  (1) - Enough warm-up.
VI_FALSE (0) - Not enough warm-up.
   D!����  �    Status                           HF %  �  �    Instrument Handle                H� > % �  d    Warmed-Up                          	               	            /    Reads out whether to be in the service mode.
        This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
        0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Reads out whether to be in the service mode.

Returned Values:
VI_TRUE  (1) - In the service mode.
VI_FALSE (0) - Not in the service mode.
   J�����  �    Status                           N� %  �  �    Instrument Handle                OQ > % �  d    Service Mode                       	               	            �    For selected port of selected channel, reads out the power calibration data array.

Notes:

(1) This function is not available for ENA E5061A/E5062A.
    S    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Port) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     M    Selects the corresponding channel.

Valid Range: 1 to 16

Default Value: 1
     4    Calibration data array reads out from instrument.
     @    Specifies port number.

Valid Range:
1 to 4

Default Value:
1
     +    Specifies buffer size of Cal Data array.
   QA����  �    Status                           U� %  �  �    Instrument Handle                V; > % �  d    Channel                          V� �� �  d    Cal Data                         V� > � �  d    Port                             W �, �  d    Array Size                         	               1    	            1    0    �    For selected port of selected channel, sets the power calibration data array.

Notes:

(1) This function is not available for ENA E5061A/E5062A.
    S    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Port) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     M    Selects the corresponding channel.

Valid Range: 1 to 16

Default Value: 1
     0    Measurement points for write into instrument.
     @    Specifies port number.

Valid Range:
1 to 4

Default Value:
1
         Number of data points.
   YK����  �    Status                           ]� %  �  �    Instrument Handle                ^E > % �  d    Channel                          ^� >� �  d    Cal Data                         ^� > � �  d    Port                             _ >+ �  d    Array Size                         	               1        1    0    f    For the active trace of selected channel, reads out the formated or corrected data or memory array.
    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Source) out of range.
BFFC0004  Parameter 4 (Correction) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Selects the corresponding channel.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA D5061A/E5062A)

Default Value: 1
     <    Data array for Primary / Real part of measurement points.
     L    Specifies array size for Primary / Real and Secondary / Imaginary arrays.
     �    Selects source of data.

Valid Values:
AGENA_DATA_SOURCE_DATA   (0)
AGENA_DATA_SOURCE_MEMORY (1)

Default Value:
AGENA_DATA_SOURCE_DATA (0)
     �    Selects correction type.

Valid Values:
AGENA_DATA_CORRECTION_FORMATTED (0)
AGENA_DATA_CORRECTION_CORRECTED (1)

Default Value:
AGENA_DATA_CORRECTION_FORMATTED (0)
     C    Data array for Secondary / Imaginary part of measurement points.
   a
����  �    Status                           e� %  �  �    Instrument Handle                f7 > % �  d    Channel                          f� � � �  d    Primary / Real                   g � % �  d    Array Size                       go > � � d    Source                           h >� � d    Correction                       h� �� �  d    Secondary / Imaginary              	               1    	            0               <Data AGENA_DATA_SOURCE_DATA Memory AGENA_DATA_SOURCE_MEMORY               TFormatted AGENA_DATA_CORRECTION_FORMATTED Corrected AGENA_DATA_CORRECTION_CORRECTED    	            a    For the active trace of selected channel, sets the formated or corrected data or memory array.
    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Source) out of range.
BFFC0004  Parameter 4 (Correction) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Selects the corresponding channel.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA E5061A/E5062A)

Default Value: 1
     <    Data array for Primary / Real part of measurement points.
     L    Specifies array size for Primary / Real and Secondary / Imaginary arrays.
     �    Selects source of data.

Valid Values:
AGENA_DATA_SOURCE_DATA   (0)
AGENA_DATA_SOURCE_MEMORY (1)

Default Value:
AGENA_DATA_SOURCE_DATA (0)
     �    Selects correction type.

Valid Values:
AGENA_DATA_CORRECTION_FORMATTED (0)
AGENA_DATA_CORRECTION_CORRECTED (1)

Default Value:
AGENA_DATA_CORRECTION_FORMATTED (0)
     C    Data array for Secondary / Imaginary part of measurement points.
   k�����  �    Status                           p} %  �  �    Instrument Handle                q > % �  d    Channel                          q� � � �  d    Primary / Real                   r  � % �  d    Array Size                       rT > � � d    Source                           r� >� � d    Correction                       s� �� �  d    Secondary / Imaginary              	               1        0               <Data AGENA_DATA_SOURCE_DATA Memory AGENA_DATA_SOURCE_MEMORY               TFormatted AGENA_DATA_CORRECTION_FORMATTED Corrected AGENA_DATA_CORRECTION_CORRECTED        M    For selected channel, reads out the frequencies of all measurement points.
    (    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Selects the corresponding channel.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA E5061A/E5062A)

Default Value: 1
     4    Returns the frequencies of all measurement points.     0    Specifies array size for Stimulus Data array.
   v�����  �    Status                           z� %  �  �    Instrument Handle                { > % �  d    Channel                          | >� �  d    Stimulus Data                    |[ > � �  d    Array Size                         	               1    	            0    M    For the active trace of selected channel, reads out the limit test result.
    w    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Fail) NULL pointer.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Selects the corresponding channel.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA E5061A/E5062A)

Default Value: 1
        For the active trace of selected channel, reads out the limit test result.

Returned Values:
VI_TRUE  (1) - The limit test result is FAIL.
VI_FALSE (0) - The limit test result is PASS.

Notes:
When the limit test is disabled, VI_FALSE (0) is always read out.
   ~����  �    Status                           �� %  �  �    Instrument Handle                �5 > % � d    Channel                          �� > � �  d    Fail                               	               1    	            �    For the active trace of selected channel, reads out the number of the measurement points and stimulus values (frequency, power level or time) at all the measurement point that failed the limit test.    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0004  Parameter 4 (Number of Failed Points) NULL pointer.
BFFC0005  Parameter 5 (Data) NULL pointer.


BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Selects the corresponding channel.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA E5061A/E5062A)

Default Value: 1
     �    For the active trace of selected channel, reads out the stimulus values (frequency, power level or time) at all the measurement point that failed the limit test.
     2    Specifies array size for limit test Data array.
     w    For the active trace of selected channel, reads out the number of the measurement points that failed the limit test.
   ������  �    Status                           �A %  �  �    Instrument Handle                �� > % �  d    Channel                          �� �� �  d    Data                             �, >� �  d    Array Size                       �f � � �  d    Number of Failed Points            	               1    	            0    	            �    For the active trace of selected channel, reads out the response value of selected marker.

When the reference marker mode is enabled, the readout value is the value relative to the reference marker.
    y    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Marker) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     ]    For the active trace of selected channel, reads out the stimulus value of selected marker.
     9    Response value (primary value) at the marker position.
     �    Selects the corresponding channel.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA E5061A/E5062B)

Default Value: 1
     �    Selects the corresponding marker.

Valid Range: 1 to 10
1 to 9 - marker1 to marker9
10     - reference marker

Default Value: 1
     �    Response value (secondary value) at the marker position.

Always 0 when the data format is not the Smith chart format or the polar format.   �'����  �    Status                           �� %  �  �    Instrument Handle                �G >� �  d    X Value                          �� � % �  d    Real Value                       �� > % � d    Channel                          �� > � � d    Marker                           � � � �  d    Imaginary Value                 ���� c W��                                            	               	           	           1    1    	           3|------------------- Y Values -------------------|    �    For the active trace of channel, returns marker flatness or filter statistics or marker statistics data.

Notes:

(1) This function is available only for ENA E5061A/E5062A.
    y    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Marker) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Selects the corresponding channel.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA E5061A/E5062B)

Default Value: 1
    .    For the active trace of channel, turn on and off the marker function.

Valid Values:
AGENA_MARKER_MATH_FLAT (0)
   - marker flatness function.

AGENA_MARKER_MATH_FST  (1)
  - RF filter statistics.

AGENA_MARKER_MATH_STAT (2)
  - marker statistics function.

Default Value:
AGENA_MARKER_MATH_FLAT (0)
     �    Returns marker flatness or filter statistics or marker statistics data.

Returns:
 Span (for flatness data)
 Loss (for filter statistics data)
 Span (for marker statistics data)     �    Returns marker flatness or filter statistics or marker statistics data.

Returns:
 Gain     (for flatness data)
 Ripple   (for filter statistics data)
 Average  (for marker statistics data)
     �    Returns marker flatness or filter statistics or marker statistics data.

Returns:
 Slope        (for flatness data)
 Attenuation  (for filter statistics data)
 Average      (for marker statistics data)
     �    Returns marker flatness or filter statistics or marker statistics data.

Returns:
 Flatness (for flatness)
 Peak to Peak (for statistics data)   �~����  �    Status                           ��   �  �    Instrument Handle                �� 3 " � d    Channel                          �> 3 � � d    Marker Function                  �t � " �  `    Num1                             �/ � � �  `    Num2                             �� �& �  `    Num3                             �� �� �  `    Num4                               	               1               mFlatness AGENA_MARKER_MATH_FLAT RF Filter Statistics AGENA_MARKER_MATH_FST Statistics AGENA_MARKER_MATH_STAT    	           	           	           	           f    For the active trace of selected channel, reads out the bandwidth search result of selected marker.
    y    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Marker) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None         Returns the bandwidth.
          Returns the center frequency.
     �    Selects the corresponding channel.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA E5061A/E5062A)

Default Value: 1
     �    Selects the corresponding marker.

Valid Range: 1 to 10
1 to 9 - marker1 to marker9
10     - reference marker

Default Value: 1
         Returns the Q value.
         Returns the loss.
   �:����  �    Status                           �� %  �  �    Instrument Handle                �Z >� �  d    Bandwidth                        �{ � % �  d    Center Frequency                 �� > % � d    Channel                          �C > � � d    Marker                           �� � � �  d    Q Value                          �� �� �  d    Loss                               	               	           	           1    1    	           	           �    For the active trace of selected channel, reads out the notch search result of selected marker.

Notes:

(1) This function is available only for ENA E5061A/E5062A.    y    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0003  Parameter 3 (Marker) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None         Returns the bandwidth.
          Returns the center frequency.
     �    Selects the corresponding channel.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA E5061A/E5062A)

Default Value: 1
     �    Selects the corresponding marker.

Valid Range: 1 to 10
1 to 9 - marker1 to marker9
10     - reference marker

Default Value: 1
         Returns the Q value.
         Returns the loss.
   ��|���  �    Status                           �(   �  �    Instrument Handle                �� 3� �  d    Bandwidth                        �� ~ 2 �  d    Center Frequency                 � 3 2 � d    Channel                          �� 3 � � d    Marker                           �: ~ � �  d    Q Value                          �Y ~� �  d    Loss                               	               	           	           1    1    	           	          m    For the active trace of selected channel, reads out the number of data pairs and analysis result of the agena_actExecuteAnalysis function.

Note:

(1) For the analysis of the mean value or the search of the maximum value, 1 is always read out; for the search of all peaks or the search of all targets, the total number of searched measurement points is read out.
    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.
BFFC0004  Parameter 4 (Number of Analysis Results) is NULL pointer.
BFFC0005  Parameter 5 (Stimulus) is NULL pointer.
BFFC0006  Parameter 6 (Response) is NULL pointer.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     M    Selects the corresponding channel.

Valid Range: 1 to 16

Default Value: 1
     3    Returns response value or analysis result array.
     �    Specifies array size for Stimulus and Response arrays.

Notes:
Number of points returned from instrument is specified in agena_dataReadNumberAnalysisResults function.
     �    Stimulus value of the searched measurement points.

Always set to 0 for the analysis of maximum and minimum values/standard deviation/mean value.
     �    For the active trace of selected channel, reads out the number of data pairs of the analysis result of the agena_actExecuteAnalysis function.
   ������  �    Status                           �� %  �  �    Instrument Handle                �S >  �  d    Channel                          �� >� �  `    Stimulus                         �� > � �  d    Array Size                       �� �� �  `    Response                         �0 >, �  `    Number of Analysis Results         	               1    	            0    	            	            �    This function reads out data inputted to ports C, D or E (C0 to
C3, D0 to D3 or C0 to D3).

Notes:
(1) Ports C or D must be set to input mode for read out from the port C or D.

(2) Ports C and D must be set to input mode for read out from the port E.
    %    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Port) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Selects handler port id.

Valid Values:
AGENA_HANDLER_PORT_C (2)
AGENA_HANDLER_PORT_D (3)
AGENA_HANDLER_PORT_E (4)
AGENA_HANDLER_PORT_F (5)


Default Value:
AGENA_HANDLER_PORT_F (5)
     0    Returns input data.

Returned Values:
0 to 15
   �����  �    Status                           ɬ %  �  �    Instrument Handle                �K > % � d    Port                             � > � �  `    Data                               	                         EC AGENA_HANDLER_PORT_C D AGENA_HANDLER_PORT_D E AGENA_HANDLER_PORT_E    	           �    This function outputs data to output port A (A0 to A7), port B (B0 to B7), port C (C0 to C3), port D (D0 to D3), port E (C0 to D3) or port F (A0 to B7).

Notes:
(1) Ports C or D must be set to output mode for set to the port C or D.

(2) Ports C and D must be set to output mode for set to the port E.

(3) Data is outputted as 8-bit binary (for port A and B) using x0 as LSB and x7 as MSB. Where x is port name.

(4) Data is outputted as 4-bit binary (for port C and D) using x0 as LSB and x3 as MSB. Where x is port name.

(5) Data is outputted as 8-bit binary (for port E) using C0 as LSB and D3 as MSB.

(6) Data is outputted as 16-bit binary (for port F) using A0 as LSB and B7 as MSB.
    %    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Port) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Sets output data.

Valid Range:
For port A, B and E:
0 to 255

For port C and D:
0 to 15

For port F:
0 to 65535

Default Value:
1
     �    Selects handler port id.

Valid Values:
AGENA_HANDLER_PORT_A (0)
AGENA_HANDLER_PORT_B (1)
AGENA_HANDLER_PORT_C (2)
AGENA_HANDLER_PORT_D (3)
AGENA_HANDLER_PORT_E (4)
AGENA_HANDLER_PORT_F (5)

Default Value:
AGENA_HANDLER_PORT_D (3)
   �D����  �    Status                           �q %  �  �    Instrument Handle                � > � �  d    Data                             ԝ > % � d    Port                               	               1              �A AGENA_HANDLER_PORT_A B AGENA_HANDLER_PORT_B C AGENA_HANDLER_PORT_C D AGENA_HANDLER_PORT_D E AGENA_HANDLER_PORT_E F AGENA_HANDLER_PORT_F    �    For the active trace of selected channel, reads out the statistics values (the mean vale, the standard deviation, and the difference between the maximum value and the minimum value) display.
    L    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFC0002  Parameter 2 (Channel) out of range.

BFFC0803  Error Interpreting the instrument's response.
BFFC0901  Channel is not displayed.
BFFC09F0  Instrument status error.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None         Returns Mean value.
         Returns Standard deviation.
     �    Selects the corresponding channel.

Valid Range: 1 to 16    (for ENA E5070B/E5071B)
             1 to 4     (for ENA E5061A/E5062A)

Default Value: 1
     T    Returns difference between the maximum value and the minimum value (Peak to Peak).   ������  �    Status                           �- %  �  �    Instrument Handle                �� >� �  d    Mean                             �� � � �  d    Standard Deviation               � > % � d    Channel                          ݰ �� �  d    Peak to Peak                       	               	           	           1    	              This function resets the instrument to a known state and sends initialization commands to the instrument that set any necessary programmatic variables such as Headers Off, Short Command form, and Data Transfer Binary to the state necessary for the operation of the instrument driver.    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None   �����  �    Status                           �M   �  �    Instrument Handle                  	               �    This function runs the instrument's self test routine and returns the test result(s).

Note:

(1) When is Self-Test Failed you read your manual.     �    This control contains the value returned from the instrument self test.  Zero means success.  For any other code, see the device's operator's manual.
     �    This control contains the string returned from the self test. See the device's operation manual for an explanation of the string's contents.

Notes:

(1) The array must contain at least 256 elements ViChar[256].    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None   �  = 2 �  `    Self Test Result                 � = � � ,    Self-Test Message                �}����  �    Status                           �"   �  �    Instrument Handle                  	           	            	               F    This function reads an error code from the instrument's error queue.     N    This control returns the error code read from the instrument's error queue.
     �    This control returns the error message string read from the instrument's error message queue.

Notes:

(1) The array must contain at least 256 elements ViChar[256].    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None   � = 2 �  `    Error Code                       �a = � � ,    Error Message                    �����  �    Status                           �   �  �    Instrument Handle                  	            	            	               �    This function takes the Status Code returned by the instrument driver functions, interprets it and returns it as a user readable string.      t    This control accepts the Status Code returned from the instrument driver functions.

Default Value:
0 - VI_SUCCESS     �    This control returns the interpreted Status Code as a user readable message string.

Notes:

(1) The array must contain at least 256 elements ViChar[256].    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

3FFF0085  VI_WARN_UNKNOWN_STATUS

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  VI_NULL   �� =  �  `    Status Code                      �^ = � � �    Message                          �����  �    Status                           ��   �  �    Instrument Handle                  0    	            	           VI_NULL   Q    This function returns the revision numbers of the instrument driver and instrument firmware, and tells the user with which  instrument firmware this revision of the driver is compatible. 

This instrument driver's Revision Number is "Rev 1.1, 08/2005, CVI 7.0" and is compatible with Instrument Firmware Revision "A.04.00" and higher.
     �    This control returns the Instrument Driver Software Revision.

Notes:

(1) The array must contain at least 256 elements ViChar[256].         This control returns the Instrument Firmware Revision.

Notes:

(1) The array must contain at least 256 elements ViChar[256].    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None   �� = 2 �  �    Instrument Driver Revision       �N =, �  �    Firmware Revision                ������  �    Status                            z   �  �    Instrument Handle                  	            	            	               �    This function performs the following operations:
viClose (instrSession) and viClose (rmSession).

Notes:

(1) The instrument must be reinitialized to use it again.    �    This control contains the status code returned by the function call.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  No listeners condition was detected.
BFFF0060  This interface is not the controller in charge.
BFFF0067  Operation is not supported on this session.
     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None   �����  �    Status                           g   �  �    Instrument Handle                  	            ����         =  !�             K.        init                                                                                                                                    ����         #'  1�             K.        configureAppExample                                                                                                                     ����         41  @j             K.        openCalibrationExample                                                                                                                  ����         A�  M�             K.        shortCalibrationExample                                                                                                                 ����         O+  [d             K.        loadCalibrationExample                                                                                                                  ����         \�  h�             K.        thru12CalibrationExample                                                                                                                ����         j/  vt             K.        thru21CalibrationExample                                                                                                                ����         w�  ��         
    K.        appExample                                                                                                                              ����         ��  ��             K.        confChannelTrace                                                                                                                        ����         �,  ��         
    K.        confPower                                                                                                                               ����         �u  �N             K.        confFixedFreq                                                                                                                           ����         �C  �         
    K.        confSweep                                                                                                                               ����         Ѻ  �u             K.        confSweepStimulus                                                                                                                       ����         �j  �e             K.        confSweepSegments                                                                                                                       ����         �m �             K.        confIFBwid                                                                                                                              ����        � �             K.        confAveraging                                                                                                                           ����        �              K.        confSmoothing                                                                                                                           ����        W #�             K.        confAbsoluteMeasurement                                                                                                                 ����        (� <|             K.        confExtSignalSource                                                                                                                     ����        ?� XB             K.        confFreqOffset                                                                                                                          ����        \g vE             K.        confLayout                                                                                                                              ����        zh ��             K*        confDisplay                                                                                                                             ����        � ��             K.        confTraceDisplay                                                                                                                        ����        � ��             K.        confColor                                                                                                                               ����        �u �j             K.        confXAxisSegmentSweep                                                                                                                   ����        �� ��             K.        confDispCorr                                                                                                                            ����        �� �C             K.        confScale                                                                                                                               ����        � �M             K.        confCal                                                                                                                                 ����        � �a             K.        confCalKit                                                                                                                              ����        �� X             K.        confCalKitStandardOffsets                                                                                                               ����        � �             K.        confCalKitClass                                                                                                                         ����         d             K.        confPortExtension                                                                                                                       ����        � &�             K.        confECal                                                                                                                                ����        (� 2�             K.        confPowCal                                                                                                                              ����        4� =             K.        confRefCalFactor                                                                                                                        ����        >^ G9             K.        confCalibrationFactorTable                                                                                                              ����        H� P�             K.        confLossCompensationTable                                                                                                               ����        R� Z�             K.        confScalarCal                                                                                                                           ����        \� c�             K.        confRecCal                                                                                                                              ����        e pR             K.        confTrigger                                                                                                                             ����        r� {�             K.        confLimitTest                                                                                                                           ����        }� �g         	    K.        confLimitTestTable                                                                                                                      ����        �r �G             K.        confMarker                                                                                                                              ����        �� �s             K.        confActiveMarker                                                                                                                        ����        �a ��             K.        confMarkerMode                                                                                                                          ����        �� �-             K.        confMarkerSearch                                                                                                                        ����        �� �             K.        confBandwidthSearch                                                                                                                     ����        ƚ �K             K.        confMarkerFunction                                                                                                                      ����        �� ۯ             K.        confNotchSearch                                                                                                                         ����        �2 �              K.        confAnalysis                                                                                                                            ����        �z �         
    K.        confFixSim                                                                                                                              ����        6 <         	    K.        confFixSimBalUnbalConv                                                                                                                  ����        I .0             K.        confFixSimMatchingCircuitEmbedding                                                                                                      ����        2} <�             K.        confFixSimPortImpedanceConversion                                                                                                       ����        >� J�             K.        confFixSimNetworkDeembedding                                                                                                            ����        L� \�             K.        confFixSim4portNetworkDeEmbedding                                                                                                       ����        `� n�         	    K.        confTDomTransform                                                                                                                       ����        q� |~             K.        confTDomDisplayRange                                                                                                                    ����        ~� ��             K.        confTDomGating                                                                                                                          ����        �� �Y             K.        confParameterConversion                                                                                                                 ����        �= ��             G.        confHandlerIOControl                                                                                                                    ����        �� �             K.        confE5091A                                                                                                                              ����        �1 ͪ         	    K.        confDateTime                                                                                                                            ����        �� ��         	    K.        confExternalSigGen                                                                                                                      ����        �$ �%             K.        confInitialSourcePort                                                                                                                   ����        �1 �6             K.        confCorrTemp                                                                                                                            ����        �` �~             K.        actClearAvgData                                                                                                                         ����        �2 �&             K.        actCopyMeasDataToMem                                                                                                                    ����        �� k             K.        actAutoscaleYAxis                                                                                                                       ����        Y 	9             K.        actResetCalKit                                                                                                                          ����        	�              K.        actMeasureCalData                                                                                                                       ����        d �             K.        actCalculateCalCoef                                                                                                                     ����        [ $�             K.        actClearCalData                                                                                                                         ����        &+ 2             K.        actExecuteECal                                                                                                                          ����        5	 <�             K.        actMeasurePowerCalData                                                                                                                  ����        >< D�             K.        actCalculateScalarCalCoef                                                                                                               ����        EW NI             K.        actClearScalarCalData                                                                                                                   ����        O� Y�             K.        actMeasureScalarCalData                                                                                                                 ����        \� e3             K.        actExecuteScalarECal                                                                                                                    ����        g o�             G.        actCalculateRecCalCoef                                                                                                                  ����        p� v�             K.        actTrigger                                                                                                                              ����        x ~�             K.        actSweepStart                                                                                                                           ����        � ��             K.        actSweepAbort                                                                                                                           ����        �5 ��             K.        actSweAvgReset                                                                                                                          ����        �? ��             K.        actMarkerSearch                                                                                                                         ����        �* ��             K.        actSetMarkerValues                                                                                                                      ����        �� ��             K.        actExecuteAnalysis                                                                                                                      ����        �` ��             K.        actTDomMatchFreqRange                                                                                                                   ����        �b �-             K.        actStoreInstrumentState                                                                                                                 ����        �� �             K.        actStore                                                                                                                                ����        ̑ �+             K.        actRecall                                                                                                                               ����        �: �&             K.        actStoreChannelState                                                                                                                    ����        �L �=             K.        actStoreChannelCoefficient                                                                                                              ����        �c �             K.        actRecallChannelState                                                                                                                   ����        �= �8             K.        actRecallChannelCoefficient                                                                                                             ����        �^ �p             K.        actClearChannelState                                                                                                                    ����        �� *             K.        actFileManager                                                                                                                          ����        � K             K.        actFileTransferToStorage                                                                                                                ����        s              K.        actFileTransferFromStorage                                                                                                              ����        � %	             K.        actDirContents                                                                                                                          ����        &� -X             K.        actHCopy                                                                                                                                ����        .P 4�             K.        actSystemInfo                                                                                                                           ����        6; ;&             K.        actShutdown                                                                                                                             ����        ;� BX             K.        actSecurityLevel                                                                                                                        ����        Co I�             K.        actWarmedUp                                                                                                                             ����        JV O�             K.        actServMode                                                                                                                             ����        P� WG             K.        dataReadCalDataArr                                                                                                                      ����        X� _;             K.        dataWriteCalDataArr                                                                                                                     ����        `� h�             K.        dataReadDataMemArr                                                                                                                      ����        k� s�             K.        dataWriteDataMemArr                                                                                                                     ����        v[ |�             K.        dataReadStimulusArr                                                                                                                     ����        }� ��             K.        dataLimitFail                                                                                                                           ����        �� ��             K.        dataReadFailMeasPoints                                                                                                                  ����        �U ��             K.        dataMarkerData                                                                                                                          ����        �� �c             K.        dataMathMarkerData                                                                                                                      ����        �� �             K.        dataMarkerBandwidthSearchResult                                                                                                         ����        �� �u             K.        dataMarkerNotchSearchResult                                                                                                             ����        �g ��             K.        dataReadAnalysisResult                                                                                                                  ����        �y �C             K.        dataReadHandlerInput                                                                                                                    ����        ̇ Վ             K.        dataWriteHandlerOutput                                                                                                                  ����        � �             K.        dataTraceStatisticAnalysisResult                                                                                                        ����        ߃ ��             K.        reset                                                                                                                                   ����        �f ��             K.        self_test                                                                                                                               ����        � �S             K.        error_query                                                                                                                             ����        �O �k             K.        error_message                                                                                                                           ����        �g              K.        revision_query                                                                                                                          ����                      K.        close                                                                                                                                                                                                                              �Initialize                                                                          �Application Functions                                                                �Configuration Application Example                                                    �Open Calibration Example                                                             �Short Calibration Example                                                            �Load Calibration Example                                                             �Thru Between Port 1 and Port 2 Calibration Example                                   �Thru Between Port 2 and Port 1 Calibration Example                                   �Application Example                                                                 ?Configuration Functions                                                             �Measurement Conditions                                                               �Configure Channel And Trace                                                          �Configure Power                                                                      �Configure Fixed Frequency                                                           	Sweep Configuration                                                                  �Configure Sweep                                                                      �Configure Sweep Stimulus                                                             �Define Sweep Segments Table                                                          �Configure IF Bandwidth                                                               �Configure Averaging                                                                  �Configure Smoothing                                                                  �Configure Absolute Measurement                                                       �Configure External Signal Source                                                     �Configure Frequency Offset                                                          	CScreen Display                                                                       �Configure Layout                                                                     �Configure Display                                                                    �Configure Trace Display                                                              �Configure Color                                                                      �Configure X Axis For Segment Sweep                                                   �Configure Corrections                                                                �Configure Scale                                                                     	�Calibration Configuration                                                            �Configure Calibration                                                               	�Calibration Kits                                                                     �Configure Calibration Kit                                                            �Configure Standard Offsets                                                           �Configure Class                                                                      �Configure Port Extension                                                             �Configure ECal                                                                      
Power Calibration Configuration                                                      �Configure Power Calibration                                                          �Configure Reference Calibration Factor                                               �Configure Calibration Factor Table                                                   �Configure Loss Compensation Table                                                    �Configure Scalar-Mixer Calibration                                                   �Configure Receiver Calibration                                                       �Configure Trigger                                                                   
NLimit Test                                                                           �Configure Limit Test                                                                 �Configure Limit Test Table                                                          
�Marker Configuration                                                                 �Configure Marker                                                                     �Configure Active Marker                                                              �Marker Mode                                                                          �Configure Marker Search                                                              �Configure Bandwidth Search                                                           �Configure Marker Function                                                            �Configure Notch Search                                                              
�Analysis Configuration                                                               �Configure Analysis                                                                  
�Fixture Simulator Configuration                                                      �Configure Fixture Simulator                                                          �Configure Balance Unbalance Conversion                                               �Configure Matching Circuit Embedding                                                 �Configure Port Impedance Conversion                                                  �Configure Network De-embedding                                                       �Configure 4-port Network (De-)Embedding                                             BTime Domain Configuration                                                           |Transform Configuration                                                              �Configure Time Domain Transform                                                      �Configure Time Domain Display Range                                                  �Configure Time Domain Gating                                                         �Configure Parameter Conversion                                                       �Configure Handler IO Control                                                         �Configure Controlling E5091A                                                        �System Configuration                                                                 �Configure Date And Time                                                              �Configure External Signal Generator                                                  �Configure Initial Source Port                                                        �Configure Correction and Temperature                                                Action/Status Functions                                                             �Measurement Conditions                                                               �Clear Averaging Data                                                                �Screen Display                                                                       �Copy Measurement Data To MEM                                                         �Autoscale Y Axis                                                                    $Calibration                                                                          �Reset Calibration Kit                                                                �Measure Calibration Data                                                             �Calculate Calibration Coefficients                                                   �Clear Calibration Data                                                               �Execute ECal                                                                        lPower Calibration                                                                    �Measure Power Calibration Data                                                      �Scalar-Mixer Calibration                                                             �Calculate Scalar-Mixer Calibration Coefficients                                      �Clear Scalar-Mixer Calibration Data                                                  �Measure Scalar-Mixed Calibration Data                                                �Execute Scalar-Mixer ECal                                                            �Calculate Receiver Calibration Coefficients                                          �Send Trigger                                                                        �Sweep                                                                                �Start Sweep                                                                          �Abort Sweep                                                                          �Restart Average                                                                     *Marker                                                                               �Marker Search                                                                        �Set Marker Values                                                                   gAnalysis                                                                             �Execute Analysis                                                                    �Time Domain                                                                          �Match Frequency Range                                                               �File Handling                                                                        �Store Instrument State                                                               �Store                                                                                �Recall                                                                               �Store Channel State                                                                  �Store Channel Coefficient                                                            �Recall Channel State                                                                 �Recall Channel Coefficient                                                           �Clear Channel State                                                                  �File Manager                                                                         �File Transfer To Storage Device                                                      �File Transfer From Storage Device                                                    �Directory Contents                                                                  ,System                                                                               �Hardcopy                                                                             �Read System Informations                                                             �Shutdown                                                                             �Security Level                                                                       �Read Warmed-Up State                                                                 �Read Service Mode State                                                             iData Functions                                                                      �Calibration                                                                          �Read Calibration Data Array                                                          �Write Calibration Data Array                                                         �Read Data and Memory Arrays                                                          �Write Data and Memory Arrays                                                         �Read Stimulus Array                                                                 �Limit Test                                                                           �Limit Fail                                                                           �Read Fail Meas Points                                                               8Marker                                                                               �Marker Data                                                                          �Math Marker Data                                                                     �Marker Bandwidth Search Result                                                       �Marker Notch Search Result                                                           �Read Analysis Result                                                                uHandler IO Control                                                                   �Read Handler Input Data                                                              �Write Handler Output Data                                                            �Trace Statistic Analysis Result                                                     �Utility Functions                                                                    �Reset                                                                                �Self-Test                                                                            �Error-Query                                                                          �Error Message                                                                        �Revision Query                                                                       �Close                                                                           