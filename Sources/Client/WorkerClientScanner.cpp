
#include "WorkerClientScanner.h"

namespace Test
{

	WorkerClientScanner::WorkerClientScanner(Event& event,
		Pipe& pipe,
		std::vector<BYTE>& vecResult,
		std::mutex& mutex) :
		event(std::move(event)),
		pipe(std::move(pipe)),
		vecResult(vecResult),
		mutex(mutex)
		{ }

	std::unique_ptr<IWorker> WorkerClientScanner::Create(Event& event,
		Pipe& pipe,
		std::vector<BYTE>& vecResult,
		std::mutex& mutex)
	{

		return std::unique_ptr<IWorker>(new WorkerClientScanner(event,
			pipe,
			vecResult,
			mutex));

	}

	void WorkerClientScanner::Run(ULONG_PTR ulptrKey,
		LPOVERLAPPED lpOverlapped,
		DWORD dwRead)
	{

		try
		{

			AutoSetEvent autoSetEvent(this->event);

			auto wsFile = Convert::ToString(this->vecData);

			this->pipe->Write(this->vecData);

			this->vecData = std::vector<BYTE>(Constants::SizeBuffers::Pipe);

			auto dwRead = this->pipe->Read(this->vecData);
			
			auto wsResult = Convert::ToString({ this->vecData.cbegin(),
				this->vecData.cbegin() + dwRead });
				
			if (wsResult != Constants::wsNormal)
			{

				std::wostringstream wos{};
				wos << wsFile << L" -> " << Constants::wsVirus << L" [GUID: " << wsResult << L"]\r\n";

				auto vecTmp = Convert::ToBytes(wos.str());

				std::unique_lock<std::mutex> lock(this->mutex);

				this->vecResult.insert(this->vecResult.cend(),
					vecTmp.cbegin(),
					vecTmp.cend());

			}


		}
		catch (const WinApiException& ex)
		{

			IWorker::SetErrCode(ex.GetErrCode() ? ex.GetErrCode() : ERROR_CONTINUE);
			throw;

		}
		catch (...)
		{

			IWorker::SetErrCode(ERROR_CONTINUE);
			throw;

		}

	}

	WorkerClientScanner::operator HANDLE(void) const noexcept
	{

		return *this->event;

	}

	std::vector<BYTE>& WorkerClientScanner::Data(void) noexcept
	{

		return this->vecData;

	}

}
