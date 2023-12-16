#pragma once

#include "../AA_PreCompiledHeaders.h"
#include "Engine/Core/Core.h"

namespace AAEngine {
	
	/*
	* EventType => Type of the event
	* 
	* Window Events => Anything related to windows
	* Mouse Events => Anything related to mouse input
	* Keyboard Events => Anything related to keybpard input
	*/
	enum class EEventType
	{
		None = 0,
		Window_CloseEvent, Window_ResizeEvent, Window_MovedEvent, Window_FocusedEvent, Window_LostFocusEvent,
		Mouse_ButtonPressedEvent, Mouse_ButtonReleasedEvent, Mouse_MovedEvent, Mouse_ScrollEvent,
		Keyboard_KeyPressedEvent, Keyboard_KeyReleasedEvent
	};

	/*
	* EventCategory => Category of the particular event
	*
	* Window => Anything related to windows
	* Input => Anything related to input
	* Mouse => Anything related to mouse
	* Keyboard => Anything related to keybpard
	*/
	enum EEventCategory
	{
		None = 0,
		EventCategory_ApplicationEvent = BIT(1),
		EventCategory_InputEvent = BIT(2),
		EventCategory_MouseEvent = BIT(3),
		EventCategory_KeyboardEvent = BIT(4),
	};
	
/*
* MACRO to initialize pure virtual type functions in sub classed events from the base Event class
*
* GetStaticType() - A static function to get the EventType
* GetEventType() - A member function to get the EventType
* GetName() - A member function to get the name of the EventType
*/
#define EVENT_CLASS_TYPE(Type)			static EEventType GetStaticType() { return EEventType::##Type; } \
										virtual EEventType GetEventType() const override { return GetStaticType(); } \
										virtual const char* GetName() const override { return #Type; }

/*
* MACRO to initialize pure virtual category functions in sub classed events from the base Event class
*
* GetCategoryFlags() - A member function to get all the categories an Event lives in, using one integer
*/
#define EVENT_CLASS_CATEGORY(Category)	virtual int GetCategoryFlags() const override { return Category; }

	/*
	* Event class to define an Event
	*
	* Any Event that comes in to be handled from the Application passes through this Event class
	* i.e. This Event class defines and decribes any and every Event that comes in from the Application
	*/
	class AA_ENGINE_API CEvent
	{
	public:
		friend class CEventHandler;

		/*
		* Default Constructor for the Event class
		*/
		CEvent() = default;

		/*
		* Pure Virtual Function to return the EventType of the Event
		* 
		* @returns EEventType of the Event
		*/
		virtual EEventType GetEventType() const = 0;
		/*
		* Pure Virtual Function to return the Category Flags for an Event
		*
		* @returns Integer with Bit wise Flags for Categories
		*/
		virtual int GetCategoryFlags() const = 0;
		/*
		* Pure Virtual Function to return the Name of the Event
		*
		* @returns const char* of the Name of the Event
		*/
		virtual const char* GetName() const = 0;

		/*
		* Virtual Function to return an std::string for the Event
		* Useful for Logging Events
		*
		* @returns Event represented as a String
		*/
		virtual std::string ToString() const { return GetName(); }

		/*
		* Virtual Function to return whether the Event is of a Category or not
		* Useful for Logging Events
		*
		* @params Category - Category to check this Events category against
		* 
		* @returns true if Event Category == Category, false otherwise
		*/
		virtual bool IsOfCategory(EEventCategory Category)
		{
			return GetCategoryFlags() & Category;
		}

	protected:
		/*
		* bool to store whether the Event is Handled or not
		*/
		bool bHandled = false;
	};

	/*
	* Event Handler class to Handle any incoming Events.
	*
	* Any Event that needs to be handled from the Application uses this EventHandler class
	*/
	class AA_ENGINE_API CEventHandler
	{
	public:
		/*
		* EventFunction with templated EventType argument.
		* 
		* @param EventType - Takes in the EventType to be able to process specific events
		* 
		* @returns true if Event Handler is handling that particular Event, false otherwise
		*/
		template<typename TemplateEventType>
		using EventFunction = std::function<bool(TemplateEventType&)>;

		/*
		* Constructor that takes in a Ref to an Event and initializes MEvent variable.
		* This means this CEventHandler class that handled MEvent.
		* 
		* @param CEvent& - Event reference (to avoid extra memory storage) used for Handled this Event
		*/
		CEventHandler(CEvent& MEvent)
			: mEvent(MEvent) {}

		/*
		* Handle Event function that calls the passed in Event with the EventType argument letting the user define the Event Handling Logic.
		*
		* @param EventFunction<TemplateEventType> - Event Function to handle the particular Event
		* 
		* @return true if EventFunctions type matches the EventType => EventFunction was called, return false otherwise
		*/
		template<typename TemplateEventType>
		FORCEINLINE bool HandleEvent(EventFunction<TemplateEventType> Function)
		{
			if (mEvent.GetEventType() == TemplateEventType::GetStaticType())
			{
				mEvent.bHandled = Function(static_cast<TemplateEventType&>(mEvent));
				return true;
			}
			return false;
		}
	private:
		/*
		* Event Reference that can be handled by this CEventHandler
		*/
		CEvent& mEvent;
	};

	inline std::ostream& operator<< (std::ostream& OStream, const CEvent& Event)
	{
		return OStream << Event.ToString();
	}
}

