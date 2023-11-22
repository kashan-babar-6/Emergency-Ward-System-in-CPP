# Emergency-Ward-System-in-CPP

In this Emergency Ward System (EWS), we are managing patients and scheduling their operations. This way doctor can operate each patient efficiently.

Problem Statement:
	In emergency ward, managing patients is a lot of hassle. Doctors have to face many issues like which patient should we operate first.
  With this system, doctors will get the preplanned schedule with all the details like 	which patient should be operated first and how much an operation should take?
  This will be scheduled on the 	basis of condition of the patient. Critical patients will be our first priority. This way scheduling will be 	fair and efficient.

Methodology:

	We use Priority Scheduling in this system. Non preemptive approach is used here because the operation can’t be interrupted in between its procedure.
 
		• Priority goes from highest to lowest as 1 to 4.

		• At same time if two patients came then higher priority patient will be operated first.

		• If two patients have same priority level then we will operate the patient first who came earlier.

		• After operating every patient in queue, their data will be saved in the file using file handling.

		• At last, we can calculate the overall stats of the patient like avg turnaround time and waiting time to check the efficiency of the scheduling
      and record saving purpose.

![image](https://github.com/kashan-babar-6/Emergency-Ward-System-in-CPP/assets/151045286/9a083105-ef37-45a0-ab0f-0b43adb3c431)

