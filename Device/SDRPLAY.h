/*
	Copyright(c) 2021-2022 jvde.github@gmail.com

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include "Device.h"

#ifdef HASSDRPLAY
#include <sdrplay_api.h>
#endif

namespace Device {

	class SDRPLAY : public Device //, public StreamOut<RAW>
	{

#ifdef HASSDRPLAY

		// Data is processed in seperate thread
		std::thread run_thread;
		void Run();

		FIFO fifo;
		std::vector<CFLOAT32> output;

		// SDRPLAY specific
		static int API_count;

		sdrplay_api_DeviceT device;
		sdrplay_api_DeviceParamsT* deviceParams = NULL;
		sdrplay_api_RxChannelParamsT* chParams = NULL;
		;

		int LNAstate = 5;
		int gRdB = 40;
		bool AGC = true;

		static void callback_static(short* xi, short* xq, sdrplay_api_StreamCbParamsT* params, unsigned int numSamples, unsigned int reset, void* cbContext);
		static void callback_event_static(sdrplay_api_EventT eventId, sdrplay_api_TunerSelectT tuner, sdrplay_api_EventParamsT* params, void* cbContext);

		void callback(short* xi, short* xq, sdrplay_api_StreamCbParamsT* params, unsigned int numSamples, unsigned int reset);
		void callback_event(sdrplay_api_EventT eventId, sdrplay_api_TunerSelectT tuner, sdrplay_api_EventParamsT* params);

		bool running = false;

	public:
		// Control
		void Open(uint64_t h);
		void Play();
		void Stop();
		void Close();

		virtual bool isCallback() { return true; }

		void getDeviceList(std::vector<Description>& DeviceList);

		SDRPLAY();
		~SDRPLAY();

		// Settings
		void Print();
		void Set(std::string option, std::string arg);
#endif
	};
}
