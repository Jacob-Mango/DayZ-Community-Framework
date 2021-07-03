class CF_SliderWidget : CF_UIWidget
{
	reference string Min;
	reference string Max;
	reference string Current;
	
	protected SliderWidget _SliderWidget;

	override void GetProperties()
	{
		CF_Trace trace(this, "GetProperties");

		super.GetProperties();
		
		AddProperty(Min, "Min");
		AddProperty(Max, "Max");
		AddProperty(Current, "Current");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);

		super.OnWidgetScriptInit(w);
		Class.CastTo(_SliderWidget, w);
	}
	
	void OnView_Min(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Min", "" + model, evt.String());

		EnScript.SetClassVar(model, Min, 0, _SliderWidget.GetMin());
	}

	void OnModel_Min(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Min", "" + model, evt.String());

		OnView_Min(model, evt);
	}

	void OnView_Max(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Max", "" + model, evt.String());

		EnScript.SetClassVar(model, Max, 0, _SliderWidget.GetMax());
	}

	void OnModel_Max(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Max", "" + model, evt.String());

		OnView_Max(model, evt);
	}

	void OnView_Current(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Current", "" + model, evt.String());

		float _value = _SliderWidget.GetCurrent();
		EnScript.SetClassVar(model, Current, 0, _value);
	}

	void OnModel_Current(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Current", "" + model, evt.String());

		float _value;
		EnScript.GetClassVar(model, Current, 0, _value);
		_SliderWidget.SetCurrent(_value);
	}
};