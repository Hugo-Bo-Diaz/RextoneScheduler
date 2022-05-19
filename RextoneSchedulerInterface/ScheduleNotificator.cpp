#include "stdafx.h"
#include "ScheduleNotificator.h"
#include "DataHandler.h"
#include "SysTrayNotif.h"
#include "WindowClasses/WindowClass.h"
#include "StringToWstring.h"
#include "Settings.h"

ScheduleNotificator* SNotif = nullptr;

ScheduleNotificator & ScheduleNotificator::Get()
{
	if (SNotif == nullptr)
		SNotif = new ScheduleNotificator();

	return *SNotif;
}

void ScheduleNotificator::GetEvents()
{
	time_t now = time(NULL);

	DataToHappen.clear();

	std::vector<Data*>* alldata = DataHandler::Get().GetData();

	for (Data* d : *alldata)
	{
		if (IsDataOnNotifyList(d))
		{
			continue;
		}

		switch (d->type)
		{
		case DataType::DT_ToDo:
			if (((ToDo*)d)->expiration > now)
			{
				DataToHappen.push_back(DataToNotify(d->id, ((ToDo*)d)->expiration));
			}
			break;
		case DataType::DT_event:
			if (((Event*)d)->time_end > now)
			{
				DataToHappen.push_back(DataToNotify(d->id, ((Event*)d)->time_start, ((Event*)d)->time_end));
			}
			break;
		default:
			break;
		}
	}

	TimerFuncCheckTimes(CommWindow, WM_TIMER, IDTIMER_CHECK, NULL);
}

void ScheduleNotificator::Initialize(HINSTANCE hinst)
{

	Wclass = new WindowClass(hinst, TimerFuncCheckTimes, L"ScheduleNotificatorClass");
	Wclass->RegsiterWClass();

	CommWindow = CreateWindowW(Wclass->ClassName, NULL, NULL, 0, 0, 0, 0, HWND_MESSAGE, NULL, NULL, NULL);
	//set to 5 min interval
	SetTimer(CommWindow, IDTIMER_CHECK, 300000, (TIMERPROC)NULL);
	//SetTimer(NULL, IDTIMER_GET, 5000, TimerFuncGetEvents);
}

ScheduleNotificator::ScheduleNotificator()
{
}

ScheduleNotificator::~ScheduleNotificator()
{
}

bool ScheduleNotificator::IsDataOnNotifyList(Data * d)
{
	for (DataToNotify dn : DataToHappen)
	{
		if (d->id == dn.id)
			return true;
	}

	return false;
}

LRESULT CALLBACK TimerFuncCheckTimes(HWND window, UINT wm_timer, WPARAM id_timer, LPARAM current_sys_time)
{
	//SysTrayNotif::Get().SendNotification();
	if (wm_timer == WM_TIMER && id_timer == ScheduleNotificator::Get().IDTIMER_CHECK)
	{
		time_t now = time(NULL);

		for (auto dn = ScheduleNotificator::Get().DataToHappen.begin(); dn != ScheduleNotificator::Get().DataToHappen.end(); /*++i removed to be able to delete inside the loop*/)
		{
			//an event is about to happen!
			Data* d = DataHandler::Get().GetEntry(dn->id);
			
			int time_thresh = 3600;
			bool notify = true;
			switch (d->type)
			{
			case DataType::DT_event:
				time_thresh = Settings::Get().GetSettingsValue("TimeToEventNotif", 3600);
				notify = Settings::Get().GetSettingsValue("ActiveEventNotif", true);
				break;
			case DataType::DT_ToDo:
				time_thresh = Settings::Get().GetSettingsValue("TimeToToDoNotif", 3600);
				notify = Settings::Get().GetSettingsValue("ActiveToDoNotif", true);
				break;
			default:
				break;
			}

			int time_diff = abs(now - dn->time_happening);
			time_t happening = dn->time_happening;
			time_t ending = dn->time_ending;
			if ((happening > now || ending > now) && time_diff < time_thresh && notify)
			{

				if (dn == ScheduleNotificator::Get().DataToHappen.begin())
				{
					ScheduleNotificator::Get().DataToHappen.erase(dn);
					dn = ScheduleNotificator::Get().DataToHappen.begin();
				}
				else
				{
					ScheduleNotificator::Get().DataToHappen.erase(dn);
				}


				if (d == nullptr)
				{
					continue;
				}

				std::wstring title;
				std::wstring description;

				switch (d->type)
				{
				case DataType::DT_ToDo:
					title += L"Task '";
					break;
				case DataType::DT_event:
					title += L"Event '";
					break;
				default:
					break;
				}

				std::wstring notif_display_name;

				if (d->name.length() > 41)
				{
					notif_display_name = s2ws(d->name.substr(0, 35) + "...");
				}
				else
				{
					notif_display_name = s2ws(d->name);
				}

				if (happening<now && ending>now)
				{
					title += notif_display_name + L"' is happening now!";

				}
				else
				{
					title += notif_display_name + L"' is due soon!";

				}

				description += s2ws(d->description);

				SysTrayNotif::Get().SendNotification(title.c_str(), description.c_str());

			}
			else
			{
				dn++;
			}


		}
	}

	return DefWindowProc(window, wm_timer, id_timer, current_sys_time);
}
