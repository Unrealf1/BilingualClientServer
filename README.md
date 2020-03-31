# BilingualClientServer
Test task for JetBrains internship

Server is written in python, client is written in C. Port 4321 is used for communication.

Scripts at the root folder:<br>
    run "buildAll.sh" to build everything<br>
    run "runClientServer.sh n", where n is an integer to run server, n clients and close the everything automatically<br>
    run "buildAndRun.sh n" to execute both scripts above in the same order.<br>

Scripts in "client" and "server" folders are self-explanatory with one important feature: "start.sh" in "server" directory does not block the terminal. All of the scripts are working only when called from their own directory.
