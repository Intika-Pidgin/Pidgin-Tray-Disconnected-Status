# Pidgin_Notify_Disconnected_To_Tray_Icon
Patched version of pidgin to change the tray icon when an account is disconnected or network is down 

Following those ignored tickets :
https://developer.pidgin.im/ticket/1152
https://developer.pidgin.im/ticket/181
etc. 

Pidgin have a serious lack when it come to notifying the connection state, when network is down, an account is no more connected or when any network error happen. 

In the default behavior, pidgin will always show the connected tray icon instead of showing a different icon like other IMs. 

This patch/version show the "away" icon when any network icon happen. it's a usable workaround awaiting dev to add the feature.

Concretely this version, change the status of all active accounts to "Away" when any network error happen and set back those account to Online/Available when the network error is resolved. Like that the tray icon is different when a network issue happen to let the user know. 

In my case i made that modification because sometime i am off the network or i change the connection from wifi to lan etc. while pidgin always notify me that i am online in the tray icon which is not correct. also when an account have a network issue pidgin default behaviour alway display online/available status. 

# Known Issue : 
i will nor correct those issue as this patched version is a workaround 
- When an account have different status from "available" while the network issue is happenning the account status is changed to away... also when the network issue is autosolved the account is set to available not the last state  

# A good solution would be : 
Adding a new status let say "network problem" and change the tray icon to that status when a network problem happen. 

# The patch :
Here is what the patch change

**pidgin-2.11.0/pidgin/gtkblist.c**
Changing those 2 funtion : **add_generic_error_dialog** and **remove_generic_error_dialog** 


  static int how_many_time_changed_to_offline = 0;

  static void
  add_generic_error_dialog(PurpleAccount *account,
                           const PurpleConnectionErrorInfo *err)
  {
	
	GtkWidget *mini_dialog;
	const char *username = purple_account_get_username(account);
	gboolean enabled =
		purple_account_get_enabled(account, purple_core_get_ui());
	char *primary;

	if (enabled)
		primary = g_strdup_printf(_("%s disconnected"), username);
	else
		primary = g_strdup_printf(_("%s disabled"), username);

	mini_dialog = pidgin_make_mini_dialog(NULL, PIDGIN_STOCK_DIALOG_ERROR,
		primary, err->description, account,
		(enabled ? _("Reconnect") : _("Re-enable")),
		(enabled ? PURPLE_CALLBACK(purple_account_connect)
		         : PURPLE_CALLBACK(generic_error_enable_cb)),
		_("Modify Account"), PURPLE_CALLBACK(generic_error_modify_cb),
		NULL);

	g_free(primary);

	g_object_set_data(G_OBJECT(mini_dialog), OBJECT_DATA_KEY_ACCOUNT,
		account);

	 if(err->type == PURPLE_CONNECTION_ERROR_NO_SSL_SUPPORT)
		pidgin_mini_dialog_add_non_closing_button(PIDGIN_MINI_DIALOG(mini_dialog),
				_("SSL FAQs"), ssl_faq_clicked_cb, NULL);

	g_signal_connect_after(mini_dialog, "destroy",
		(GCallback)generic_error_destroy_cb,
		account);

	add_error_dialog(gtkblist, mini_dialog);
	
	how_many_time_changed_to_offline = (how_many_time_changed_to_offline + 1);
	purple_savedstatus_activate(purple_savedstatus_new(NULL, PURPLE_STATUS_AWAY));
  }

  static void
  remove_generic_error_dialog(PurpleAccount *account)
  {
    PidginBuddyListPrivate *priv = PIDGIN_BUDDY_LIST_GET_PRIVATE(gtkblist);
    remove_child_widget_by_account(
      GTK_CONTAINER(priv->error_scrollbook), account);

    how_many_time_changed_to_offline = (how_many_time_changed_to_offline - 1);
    if (how_many_time_changed_to_offline < 1) {
      purple_savedstatus_activate(purple_savedstatus_new(NULL, PURPLE_STATUS_AVAILABLE));
    }
  }

                         
                 
