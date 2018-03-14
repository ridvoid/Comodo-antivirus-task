
#include "WorkerServerScanner.h"

namespace Test
{

	WorkerServerScanner::WorkerServerScanner(IScanner* pIScanner,
		Pipe& pipe) : WorkerServerScanner()
	{

		this->pIScanner = pIScanner;
		this->pipe = std::move(pipe);
		
	}

	std::unique_ptr<WorkerServerScanner> WorkerServerScanner::Create(IScanner* pIScanner,
		Pipe& pipe)
	{

		std::unique_ptr<WorkerServerScanner> uPtrReturn(new WorkerServerScanner(pIScanner,
			pipe));

		uPtrReturn->pipe->Connect(reinterpret_cast<LPOVERLAPPED>(&uPtrReturn->overlapped));

		return uPtrReturn;

	}

	void WorkerServerScanner::Run(ULONG_PTR ulptrKey,
		LPOVERLAPPED lpOverlapped,
		DWORD dwRead)
	{

		try
		{

			switch (this->overlapped.type)
			{

			case Type::Connect:
			case Type::Write:
				this->Read();
				break;

			case Type::Read:

				this->overlapped.vecBuf = this->pIScanner->Scan(Convert::ToString({this->overlapped.vecBuf.cbegin(),
					this->overlapped.vecBuf.cbegin() + dwRead }));

				this->Write();

			}

		}
		catch (const WinApiException& ex)
		{

			IWorker::SetErrCode(ex.GetErrCode());
			throw;

		}
		catch (...)
		{ 
		
			IWorker::SetErrCode(ERROR_CONTINUE);
			throw;

		}

	}

	WorkerServerScanner::operator HANDLE(void) const
	{

		return *this->pipe;

	}

	IWorker& WorkerServerScanner::SetErrCode(DWORD dwErrCode)
	{

		try
		{

			if (dwErrCode != ERROR_BROKEN_PIPE)
				throw WorkerServerScannerException(dwErrCode);

			this->Disconnect().Connect();

			return *this;

		}
		catch (const WinApiException& ex)
		{

			IWorker::SetErrCode(ex.GetErrCode());
			throw;

		}
		catch (...)
		{

			IWorker::SetErrCode(ERROR_CONTINUE);
			throw;

		}

		return *this;

	}

	std::vector<BYTE>& WorkerServerScanner::Data(void)
	{

		throw WorkerServerScannerException(L"WorkerServerScanner::Data",
			ERROR_NOT_SUPPORTED);

	}

	WorkerServerScanner& WorkerServerScanner::Connect(void)
	{

		this->overlapped = {};

		this->pipe->Connect(reinterpret_cast<LPOVERLAPPED>(&this->overlapped));

		return *this;

	}

	WorkerServerScanner& WorkerServerScanner::Read(void)
	{

		this->overlapped = Overlapped( OVERLAPPED(),
			Type::Read,
			std::vector<BYTE>(Constants::SizeBuffers::Pipe));

		this->pipe->Read(this->overlapped.vecBuf,
			reinterpret_cast<LPOVERLAPPED>(&this->overlapped));

		return *this;

	}

	WorkerServerScanner& WorkerServerScanner::Write(void)
	{

		this->overlapped = Overlapped(OVERLAPPED(),
			Type::Write,
			this->overlapped.vecBuf);
		
		this->pipe->Write(this->overlapped.vecBuf,
			reinterpret_cast<LPOVERLAPPED>(&this->overlapped));

		return *this;

	}

	WorkerServerScanner& WorkerServerScanner::Disconnect(void)
	{

		this->pipe->Disconnect();

		return *this;

	}

}
