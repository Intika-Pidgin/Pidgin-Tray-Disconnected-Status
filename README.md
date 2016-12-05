# Pidgin_Notify_Disconnected_To_Tray_Icon
Patched version of pidgin to change the tray icon when an account is disconnected or network is down 

Following those ignored tickets :

https://developer.pidgin.im/ticket/1152

https://developer.pidgin.im/ticket/181

etc. 

Pidgin have a serious lack when it comes to notifying the connection state, when network is down, an account is no more connected or when any network error happen. 

In the default behavior, pidgin will always show the connected tray icon instead of showing a different icon like other IMs. 

This patch/version show the "away" icon when any network icon happen. It’s a usable workaround awaiting dev to add the feature.

Concretely this version, change the status of all active accounts to "Away" when any network error happen and set back those account to Online/Available when the network error is resolved. Like that the tray icon is different when a network issue happen to let the user know. 

In my case i made that modification because sometime i am off the network or i change the connection from wifi to lan etc. while pidgin always notify me that i am online in the tray icon which is not correct. Also when an account have a network issue pidgin default behavior always display online/available status. 


# Pidgin Version : 
2.11.0


# Testing the patch :
**Linux :**
Download pidgin source
Replace "pidgin-2.11.0/pidgin/gtkblist.c" by the one provided here 
Compile and install 

**Windows :**
Copy pidgin.exe and pidgin.dll to install folder
or 
Use same instruction as linux


# Known Issue : 
i will nor correct those issue as this patched version is a workaround 
- When an account have different status from "available" while the network issue is happening the account status is changed to away... also when the network issue is auto solved the account is set to available not the last state  


# A good solution would be : 
Adding a new status let say "network problem" and change the tray icon to that status when a network problem happen. 


# The patch :
Here is what the patch change

**pidgin-2.11.0/pidgin/gtkblist.c**

Changing those 2 funtion **add_generic_error_dialog**, **remove_generic_error_dialog** and adding this variable **how_many_time_changed_to_offline**
