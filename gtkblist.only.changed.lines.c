
// -----------------------------------------------------------------------------------------------------
//added variable
static int how_many_time_changed_to_offline = 0;

// -----------------------------------------------------------------------------------------------------

static void
add_generic_error_dialog(PurpleAccount *account,
                         const PurpleConnectionErrorInfo *err)
{
	//added lines at the end of the function
	how_many_time_changed_to_offline = (how_many_time_changed_to_offline + 1);
	purple_savedstatus_activate(purple_savedstatus_new(NULL, PURPLE_STATUS_AWAY));
}

static void
remove_generic_error_dialog(PurpleAccount *account)
{
	//added lines at the end of the function
	how_many_time_changed_to_offline = (how_many_time_changed_to_offline - 1);
	if (how_many_time_changed_to_offline < 1) {
		purple_savedstatus_activate(purple_savedstatus_new(NULL, PURPLE_STATUS_AVAILABLE));
	}
}
