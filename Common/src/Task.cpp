/*
	Edwino Stein - 1201324411
*/

/* ************************************************************ */
/* ******************** Implementação Task ******************** */
/* ************************************************************ */

void common::sleep(unsigned int t, char unit){

	switch(unit){
		case TIME_UNIT_NANOSECONDS:
			std::this_thread::sleep_for (std::chrono::nanoseconds(t));
		break;

		case TIME_UNIT_MICROSECONDS:
			std::this_thread::sleep_for (std::chrono::microseconds(t));
		break;
		
		case TIME_UNIT_SECONDS:
			std::this_thread::sleep_for (std::chrono::seconds(t));
		break;
		
		case TIME_UNIT_MINUTES:
			std::this_thread::sleep_for (std::chrono::minutes(t));
		break;

		case TIME_UNIT_HOURS:
			std::this_thread::sleep_for (std::chrono::hours(t));
		break;

		case TIME_UNIT_MILISECONDS:
		default:
			std::this_thread::sleep_for (std::chrono::milliseconds(t));
	}
}

/* Task */

void Task::run(){
	handle();
}


/* AsyncTask */

AsyncTask::~AsyncTask(){

	if(this->isJoinable()){
		this->join();
	}

	delete this->pThread;
}

void AsyncTask::entryPoint(taskHandle handle){
	handle();
}

void AsyncTask::run(bool detachAfterInit){
	this->pThread = new std::thread(entryPoint, handle);

	if(detachAfterInit){
		this->detach();
	}
}

void AsyncTask::join(){
	this->pThread->join();
}

void AsyncTask::detach(){
	this->pThread->detach();
}

bool AsyncTask::isJoinable(){
	return this->pThread->joinable();
}