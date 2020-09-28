
Widget GetChildAtIndex(Widget widget, int index)
{
	Widget result = widget.GetChildren();
	while (index > 0) {
		result = result.GetSibling();
		index--;
	}
	
	return result;
}

class WidgetController
{	
	bool CanTwoWayBind() {
		return false;
	}

	// Base Controller Stuff
	void SetData(TypeConverter type_converter);	
	void GetData(out TypeConverter type_converter);
	
	// Collection Stuff
	void SetSelection(TypeConverter type_converter);
	void GetSelection(out TypeConverter type_converter);
	void Insert(int index, TypeConverter type_converter);
	void InsertAt(int index, TypeConverter type_converter);
	void Remove(int index, TypeConverter type_converter);
	void Set(int index, TypeConverter type_converter);
	void Move(int index, TypeConverter type_converter);
	void Swap(int index_1, int index_2);
	void Clear();
}

class WidgetControllerTemplate<Class T>: WidgetController
{
	protected T m_Widget;
	
	void SetWidget(T w)	{
		Class.CastTo(m_Widget, w);
	}
}

class ButtonWidgetController: WidgetControllerTemplate<ButtonWidget>
{
	override bool CanTwoWayBind() {
		return true;
	}
	
	override void SetSelection(TypeConverter type_converter) {
		m_Widget.SetText(type_converter.GetString());
	}
	
	override void SetData(TypeConverter type_converter) {
		m_Widget.SetState(type_converter.GetBool());
	}
	
	override void GetData(out TypeConverter type_converter) {
		type_converter.SetBool(m_Widget.GetState());
	}
}

class EditBoxWidgetController: WidgetControllerTemplate<EditBoxWidget>
{
	override bool CanTwoWayBind() {
		return true;
	}
	
	override void SetData(TypeConverter type_converter) {
		m_Widget.SetText(type_converter.GetString());
	}
	
	override void GetData(out TypeConverter type_converter) {
		type_converter.SetString(m_Widget.GetText());
	}
}

class CheckBoxWidgetController: WidgetControllerTemplate<CheckBoxWidget>
{
	override bool CanTwoWayBind() {
		return true;
	}
	
	override void SetSelection(TypeConverter type_converter) {
		m_Widget.SetText(type_converter.GetString());
	}
	
	override void SetData(TypeConverter type_converter) {
		m_Widget.SetChecked(type_converter.GetBool());
	}
	
	override void GetData(out TypeConverter type_converter) {
		type_converter.SetBool(m_Widget.IsChecked());
	}
}

class SliderWidgetController: WidgetControllerTemplate<SliderWidget>
{
	override bool CanTwoWayBind() {
		return true;
	}
	
	override void SetData(TypeConverter type_converter) {
		m_Widget.SetCurrent(type_converter.GetFloat());
	}
	
	override void GetData(out TypeConverter type_converter) {
		type_converter.SetFloat(m_Widget.GetCurrent());
	}
}


class ProgressBarController: WidgetControllerTemplate<ProgressBarWidget>
{
	override bool CanTwoWayBind() {
		return true;
	}
	
	override void SetData(TypeConverter type_converter) {
		m_Widget.SetCurrent(type_converter.GetFloat());
	}
	
	override void GetData(out TypeConverter type_converter) {
		type_converter.SetFloat(m_Widget.GetCurrent());
	}
}

class TextWidgetController: WidgetControllerTemplate<TextWidget>
{
	override void SetData(TypeConverter type_converter) {
		m_Widget.SetText(type_converter.GetString());
	}
}


class MultilineEditBoxWidgetController: WidgetControllerTemplate<MultilineEditBoxWidget>
{
	override bool CanTwoWayBind() {
		return true;
	}
	
	override void SetData(TypeConverter type_converter) {
		m_Widget.SetText(type_converter.GetString());
	}
	
	override void GetData(out TypeConverter type_converter) {
		string out_text;
		m_Widget.GetText(out_text);
		type_converter.SetString(out_text);
	}
	
	override void Insert(int index, TypeConverter type_converter){
		m_Widget.SetLine(index, type_converter.GetString());
	}
		
	override void Remove(int index, TypeConverter type_converter) {
		m_Widget.SetLine(index, string.Empty);
	}
	
	override void Set(int index, TypeConverter type_converter) {
		m_Widget.SetLine(index, type_converter.GetString());
	}
		
	override void Clear() {
		for (int i = 0; i < m_Widget.GetLinesCount(); i++)
			m_Widget.SetLine(i, string.Empty);		
	}
}

class SpacerBaseWidgetController: WidgetControllerTemplate<SpacerBaseWidget>
{
	
	override bool CanTwoWayBind() {
		return true;
	}
	
	/*
	override void SetData(TypeConverter type_converter) {
		m_Widget.SetText(type_converter.GetWidget());
	}
	
	override void GetData(out TypeConverter type_converter) {
		string out_text;
		m_Widget.GetText(out_text);
		type_converter.SetString(out_text);
	}*/
	
	override void Insert(int index, TypeConverter type_converter)
	{
		if (type_converter.GetWidget()) {
			m_Widget.AddChild(type_converter.GetWidget());
		}
	}
	
	override void InsertAt(int index, TypeConverter type_converter)
	{	
		if (type_converter.GetWidget()) {
			Widget widget_1 = GetChildAtIndex(m_Widget, index);
			m_Widget.AddChildAfter(type_converter.GetWidget(), widget_1);
		}
	}
	
	override void Remove(int index, TypeConverter type_converter) 
	{	
		if (type_converter.GetWidget()) {
			m_Widget.RemoveChild(type_converter.GetWidget());
		}
	}
	
	override void Set(int index, TypeConverter type_converter) 
	{
		Widget widget_1 = GetChildAtIndex(m_Widget, index);
		if (type_converter.GetWidget()) {
			m_Widget.AddChildAfter(type_converter.GetWidget(), widget_1);
			m_Widget.RemoveChild(widget_1);
		}
	}
	
	override void Move(int index, TypeConverter type_converter) 
	{
		Widget widget_1 = GetChildAtIndex(m_Widget, index - 1);
		if (type_converter.GetWidget() && widget_1) {
			m_Widget.RemoveChild(type_converter.GetWidget());
			m_Widget.AddChildAfter(type_converter.GetWidget(), widget_1);
		}
	}
	
	override void Swap(int index_1, int index_2) 
	{
		if (index_1 == index_2 || index_1 < 0 || index_2 < 0) return;
		if (index_1 > index_2) {
			int store = index_1;
			index_1 = index_2;
			index_2 = store;
		}
		
		Widget widget_1 = GetChildAtIndex(m_Widget, index_1);
		Widget widget_2 = GetChildAtIndex(m_Widget, index_2);
		Widget widget_3 = GetChildAtIndex(m_Widget, index_2 - 1);
		
		m_Widget.RemoveChild(widget_1);
		m_Widget.AddChildAfter(widget_1, widget_2);
		m_Widget.RemoveChild(widget_2);
		m_Widget.AddChildAfter(widget_2, widget_3);
	}		
}

class XComboBoxWidgetController: WidgetControllerTemplate<XComboBoxWidget>
{
	override bool CanTwoWayBind() {
		return true;
	}
	
	override void SetSelection(TypeConverter type_converter) {
		m_Widget.SetCurrentItem(type_converter.GetInt());
	}
	
	override void GetSelection(out TypeConverter type_converter) {
		type_converter.SetInt(m_Widget.GetCurrentItem());
	}
	
	override void Insert(int index, TypeConverter type_converter){
		m_Widget.AddItem(type_converter.GetString());
	}
	
	override void Remove(int index, TypeConverter type_converter) {
		m_Widget.RemoveItem(index);
	}
}

class ImageWidgetController: WidgetControllerTemplate<ImageWidget>
{
	override void SetData(TypeConverter type_converter) {
		if (type_converter.GetString() != string.Empty) {
			m_Widget.LoadImageFile(0, type_converter.GetString());
			m_Widget.SetImage(0);	
		}
	}
}


class TextListboxController: WidgetControllerTemplate<TextListboxWidget>
{
	override bool CanTwoWayBind() {
		return true;
	}
	
	override void SetSelection(TypeConverter type_converter) {
		for (int i = 0; i < m_Widget.GetNumItems(); i++) {
			string row_text;
			m_Widget.GetItemText(i, 0, row_text);
			if (row_text == type_converter.GetString()) {
				m_Widget.SelectRow(i);
				return;
			}
		}
	}
	
	override void GetSelection(out TypeConverter type_converter) {
		string selection;
		m_Widget.GetItemText(m_Widget.GetSelectedRow(), 0, selection);
		type_converter.SetString(selection);
	}
	
	override void Insert(int index, TypeConverter type_converter){
		m_Widget.AddItem(type_converter.GetString(), type_converter.GetParam(), 0, index);
	}
	
	override void Remove(int index, TypeConverter type_converter) {
		m_Widget.SetItem(index, string.Empty, null, 0);
	}
	
	override void Clear() {
		m_Widget.ClearItems();
	}
}

class ItemPreviewWidgetController: WidgetControllerTemplate<ItemPreviewWidget>
{
	override void SetData(TypeConverter type_converter) {
		EntityAI entity;
		if (Class.CastTo(entity, type_converter.GetObject())) {
			Print(entity.GetPosition());
			m_Widget.SetItem(entity);
			m_Widget.SetModelPosition(vector.Zero);
		}
	}
	
	override void GetData(out TypeConverter type_converter) {
		type_converter.SetParam(new Param1<EntityAI>(m_Widget.GetItem()));
	}
}


