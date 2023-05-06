#ifndef INVENTORYSCREEN_CPP
#define INVENTORYSCREEN_CPP
#include "InventoryScreen.h"

vector<LibraryMedia*> InventoryScreen::mediaToCheckoutOrBuy;
string InventoryScreen::recordTxtFile;

void InventoryScreen::AddMedia()
{
	int choice =0;

	do
	{
		cout << setfill('-') << setw(115) << "" << endl;
		cout << setfill('-') << setw(115) << "" << endl; 
		cout << setfill('-') << setw(116) << "\n" << endl;
		cout << setfill(' ') << setw(72) << "What kind of media would you like to add?\n" << endl;
		cout << setfill(' ') << setw(54) << "0. Return" << endl;
		cout << setfill(' ') << setw(53) << "1. Books" << endl;
		cout << setfill(' ') << setw(58) << "2. Newspapers" << endl;
		cout << setfill(' ') << setw(56) << "3. Journals" << endl;
	    cout << setfill(' ') << setw(60) << "4. Periodicals\n" << endl;
		cout << setfill(' ') << setw(58) << "Enter Your Choice:\t";
		cin >> choice;
		
		if (!cin) continue; //If user enters a non integer value go to next loop
		LibraryMedia* newMedia;
		if (choice == 1) newMedia = new Book();
		else if (choice == 2) newMedia = new Newspaper();
		else if (choice == 3) newMedia = new ConferenceJournal();
		else if (choice == 4) newMedia = new Periodical();
		else if (choice == 0){
			system("cls");
			return;
		}
		else {
			system("cls");
			cout << "Invalid Selection,try again" << endl;
			continue;
		}

		newMedia->SetTitle();
		newMedia->SetAuthors();
		newMedia->SetPublishers();
		newMedia->SetInventoryCount();
		newMedia->SetPrice();
		newMedia->SetCategory();
		newMedia->SetSubCategory();
		newMedia->SetDoner();

		if (choice == 1)
		{
			Book* book = dynamic_cast<Book*>(newMedia);
			book->SetMediaType(LibraryMedia::book);
			book->SetISBN();
			book->SetEdition();
			CurrentSessionInfo::mediaList.emplace_back(new Book(*book));
			delete book;
			system("cls");
			cout << "New Book Added" << endl;
		}
		else if (choice == 2) {
			Newspaper* newspaper = dynamic_cast<Newspaper*>(newMedia);
			newspaper->SetMediaType(LibraryMedia::newspaper);
			newspaper->SetPublishRate();
			CurrentSessionInfo::mediaList.emplace_back(new Newspaper(*newspaper));
			delete newspaper;
			system("cls");
			cout << "New newspaper added" << endl;
		}
		else if (choice == 3) {
			ConferenceJournal* journal = dynamic_cast<ConferenceJournal*>(newMedia);
			journal->SetMediaType(LibraryMedia::conferenceJournal);
			journal->SetDateOfConference();
			journal->SetPlaceOfConference();
			CurrentSessionInfo::mediaList.emplace_back(new ConferenceJournal(*journal));
			delete journal;
			system("cls");
			cout << "New Journal added" << endl;
		}
		else if (choice == 4) {
			Periodical* period = dynamic_cast<Periodical*>(newMedia);
			period->SetMediaType(LibraryMedia::periodical);
			period->SetPublishRate();
			CurrentSessionInfo::mediaList.emplace_back(new Periodical(*period));
			delete period;
			system("cls");
			cout << "New Periodical added" << endl;
		}
	} while (choice != 0);
}

void InventoryScreen::SearchForMedia()
{
	system("cls"); //Don't 
	int choice;
	bool returnToPrevMenu = false;
	do {
		
		cout << setfill('-') << setw(115) << "" << endl;
		cout << setfill('-') << setw(56) << " SEARCH " << setfill('-') << setw(59) << "" << endl;
		cout << setfill('-') << setw(115) << "" << endl;
		cout << endl;
		cout << setfill(' ') << setw(51) << "0. Return" << endl;
		cout << setfill(' ') << setw(60) << "1. Search By Title" << endl;
		cout << setfill(' ') << setw(61) << "2. Search By Author" << endl;
		cout << setfill(' ') << setw(64) << "3. Search By Publisher" << endl;
		cout << setfill(' ') << setw(65) << "4. Search By Department" << endl;
		cout << setfill(' ') << setw(62) << "5. Search By Subject" << endl;

		ifstream user;
		string username;
		user.open("currentUser.txt");

		if (!user.is_open()) {
			cout << "File open was not successful";
		}
		user >> username;
		user.close();

		if (username.at(0) == 'M') {// if user isAdmin
			cout << setfill(' ') << setw(61) << "6. Search By Course" << endl;
			cout << setfill(' ') << setw(60) << "7. Search By Price" << endl;
			cout << setfill(' ') << setw(73) << "8. Search By Publisher Address\n" << endl;
			//CurrentSessionInfo::SetAdmin(true);
		}
		cout << setfill(' ') << setw(58) << "Enter Your Choice:\t";

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> choice;
		system("cls");
		if (!cin) { //If they enter a a non integer value go to next loop
			cout << "Invalid selection, try again" << endl;
			continue;
		}
		switch (choice) {
		case 0:
			returnToPrevMenu = true;
			break;
		case 1:
			SearchByTitle();
			break;
		case 2:
			SearchByAuthor();
			break;
		case 3:
			SearchByPublisherName();
			break;
		case 4:
			SearchByDepartment();
			break;
		case 5:
			SearchBySubject();
			break;
		case 6:
			SearchForMedia();
			break;
		case 7:
			SearchByPrice();
			break;
		case 8:
			SearchByPublisherAddress();
			break;		
		default:
			system("cls");
			cout << "Invalid selection, try again" << endl;
		}
		
	} while (!returnToPrevMenu);
}
void InventoryScreen::printMenu() {
	int choice =0;
	bool validChoice;
	
	system("cls");
	do
	{
		cout << setfill('-') << setw(115) << "" << endl;
		cout << setfill('-') << setw(115)<<"" << endl; //setw(62) <<  " INVENTORY SCREEN " << setfill('-') << setw(53) << "" << endl;
		cout << setfill('-') << setw(116) << "\n" << endl;

		cout << setfill(' ') << setw(68) << "Select from the options below:\n" << endl;
		cout << setfill(' ') << setw(53) << "0. Return" << endl;
		cout << setfill(' ') << setw(59) << "1. Search Media" << endl;
		cout << setfill(' ') << setw(55) << "2. Checkout" << endl;
		
		ifstream user;
		string username;
		user.open("currentUser.txt");

		if (!user.is_open()) {
			cout << "File open was not successful";
		}
		user >> username;
		//user.close();

		if (username.at(0) == 'M') {
			cout << setfill(' ') << setw(57) << "3. Add Media" << endl;
		}
		user.close();
		
		cout << setfill(' ') << setw(58) << "Enter Your Choice:\t";

		cin >> choice;
		validChoice = true; //Assume choice is valid
		string fullName;

		switch (choice)
		{
		case 0:

			//Delete all pointers and then clear vector
			for (LibraryMedia* mediaPointer : mediaToCheckoutOrBuy)
			{
				delete mediaPointer;
			}
			mediaToCheckoutOrBuy.clear();
			system("cls");
			return;
		case 1:
			system("cls");
			SearchForMedia();			
			break;
		case 2: //If a user is not an admin and selects 2, make choice invlaid
			system("cls");
			//if (isGuest) {
				cout << "Enter your name: " << endl;
				getline(cin, fullName);
				system("cls");
			//}
			cout << setfill(' ') << setw(50)<< fullName << ", Ready for checkout?" << endl;
			//CheckoutBook();
			//if (CurrentSessionInfo::CheckIfAdmin()) SearchForMedia();
			//else cout << "Invalid selection, try again" << endl;
			break;
		case 3: //If a user is not an admin and selects 3, make choice invlaid
			//TODO Check if Admin
			system("cls");
			AddMedia();
			break;
		default:
			cout << "Invalid selection, try again" << endl;
			break;
		}
		
	} while (true);
	
}

void InventoryScreen::SearchByTitle() 
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	string searchTitle;
	cout << "Enter the title of the media you are looking for" << endl;
	getline(cin, searchTitle);

	//Create vector of pointers that will point to the memory of matching books found in BookList();
	vector<LibraryMedia*> matchingList;

	//Goes through Book list and checks for title that contain the user input

	for (int i = 0; i < CurrentSessionInfo::mediaList.size(); i++)
	{
		if (CurrentSessionInfo::mediaList.at(i)->GetTitle().find(searchTitle) != string::npos) {
			matchingList.push_back(CurrentSessionInfo::mediaList.at(i));
			if (matchingList.size() >= 5) {
				PrintMatchingMedia(matchingList); //If we get more than 5 matches only return the top 5
			}
		}
	}
	if (matchingList.size() == 0) { //IF we dont find any media, print out statement and then return
		cout << "No Matching Media Found";
		return;
	}
	else {
		PrintMatchingMedia(matchingList);
		
	}


}
void InventoryScreen::SearchByAuthor() 
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	string searchAuthor;
	cout << "Enter the author of the media you are looking for" << endl;
	getline(cin,searchAuthor);

	//Create vector of pointers that will point to the memory of matching books found in BookList();
	vector<LibraryMedia*> matchingList;

	//Goes through Book list and checks for title that contain the user input

	for (int i = 0; i < CurrentSessionInfo::mediaList.size(); i++)
	{
		if (CurrentSessionInfo::mediaList.at(i)->GetSearchString(0).find(searchAuthor) != string::npos) {
			matchingList.push_back(CurrentSessionInfo::mediaList.at(i));
			if (matchingList.size() >= 5) {
				PrintMatchingMedia(matchingList); //If we get more than 5 matches only return the top 5
			}
		}
	}
	if (matchingList.size() == 0) { //IF we dont find any media, print out statement and then return
		cout << "No Matching Media Found";
		return;
	}
	else {
		PrintMatchingMedia(matchingList);
	}
}
void InventoryScreen::SearchByDepartment() 
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	string searchDep;
	cout << "Enter the Department of the media you are looking for" << endl;
	getline(cin, searchDep);
	vector<LibraryMedia*> matchingList;//Create vector of pointers that will point to the memory of matching books found in BookList();
	for (int i = 0; i < CurrentSessionInfo::mediaList.size(); i++)//Goes through Book list and checks for title that contain the user input
	{
		if (CurrentSessionInfo::mediaList.at(i)->GetCategory().find(searchDep) != string::npos) {
			matchingList.push_back(CurrentSessionInfo::mediaList.at(i));
			if (matchingList.size() >= 5) {
				PrintMatchingMedia(matchingList); //If we get more than 5 matches only return the top 5
			}
		}
	}
	if (matchingList.size() == 0) { //IF we dont find any media, print out statement and then return
		cout << "No Matching Media Found";
		return;
	}
	else {
		PrintMatchingMedia(matchingList);
	}
}
void InventoryScreen::SearchBySubject() 
{
	string searchSub;
	cout << "Enter the Department of the media you are looking for" << endl;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin >> searchSub;
	vector<LibraryMedia*> matchingList;//Create vector of pointers that will point to the memory of matching books found in BookList();
	for (int i = 0; i < CurrentSessionInfo::mediaList.size(); i++)//Goes through Book list and checks for title that contain the user input
	{
		if (CurrentSessionInfo::mediaList.at(i)->GetSubCategory().find(searchSub) != string::npos) {
			matchingList.push_back(CurrentSessionInfo::mediaList.at(i));
			if (matchingList.size() >= 5) {
				PrintMatchingMedia(matchingList); //If we get more than 5 matches only return the top 5
			}
		}
	}
	if (matchingList.size() == 0) { //IF we dont find any media, print out statement and then return
		cout << "No Matching Media Found";
		return;
	}
	else {
		PrintMatchingMedia(matchingList);
	}
}
void InventoryScreen::SearchByPublisherName()
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	string searchName;
	cout << "Enter the publisher's name of the media you are looking for" << endl;
	getline(cin, searchName);
	vector<LibraryMedia*> matchingList;//Create vector of pointers that will point to the memory of matching books found in BookList();
	for (int i = 0; i < CurrentSessionInfo::mediaList.size(); i++)//Goes through Book list and checks for title that contain the user input
	{
		if (CurrentSessionInfo::mediaList.at(i)->GetSearchString(1).find(searchName) != string::npos) {
			matchingList.push_back(CurrentSessionInfo::mediaList.at(i));
			if (matchingList.size() >= 5) {
				PrintMatchingMedia(matchingList); //If we get more than 5 matches only return the top 5
			}
		}
	}
	if (matchingList.size() == 0) { //IF we dont find any media, print out statement and then return
		cout << "No Matching Media Found";
		return;
	}
	else {
		PrintMatchingMedia(matchingList);
	}
}
void InventoryScreen::SearchByPrice()
{
	double searchPrice;
	cout << "Enter the Price of the media you are looking for" << endl;
	cin >> searchPrice;
	vector<LibraryMedia*> matchingList;//Create vector of pointers that will point to the memory of matching books found in BookList();
	for (int i = 0; i < CurrentSessionInfo::mediaList.size(); i++)//Goes through Book list and checks for title that contain the user input
	{
		if (CurrentSessionInfo::mediaList.at(i)->GetPrice() == searchPrice) {
			matchingList.push_back(CurrentSessionInfo::mediaList.at(i));
			if (matchingList.size() >= 5) {
				PrintMatchingMedia(matchingList); //If we get more than 5 matches only return the top 5
			}
		}
	}
	if (matchingList.size() == 0) { //IF we dont find any media, print out statement and then return
		cout << "No Matching Media Found";
		return;
	}
	else {
		PrintMatchingMedia(matchingList);
	}
}
void InventoryScreen::SearchByPublisherAddress()
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	string searchAdd;
	cout << "Enter the publisher's address of the media you are looking for" << endl;
	getline(cin, searchAdd);
	vector<LibraryMedia*> matchingList;//Create vector of pointers that will point to the memory of matching books found in BookList();
	for (int i = 0; i < CurrentSessionInfo::mediaList.size(); i++)//Goes through Book list and checks for title that contain the user input
	{
		if (CurrentSessionInfo::mediaList.at(i)->GetSearchString(2).find(searchAdd) != string::npos) {
			matchingList.push_back(CurrentSessionInfo::mediaList.at(i));
			if (matchingList.size() >= 5) {
				PrintMatchingMedia(matchingList); //If we get more than 5 matches only return the top 5
			}
		}
	}
	if (matchingList.size() == 0) { //IF we dont find any media, print out statement and then return
		cout << "No Matching Media Found";
		return;
	}
	else {
		PrintMatchingMedia(matchingList);
	}
}
void InventoryScreen::PrintMatchingMedia(vector<LibraryMedia*> mediaList) 
{
	
	int choice=0;
	do
	{
		cout << "Select a media" << endl;
		for (int i = 1; i <= mediaList.size(); i++)
		{
			cout << i << ". ";
			mediaList.at(i-1)->ToString();
		}
		cout << "0. Return" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> choice;
		if (choice == 0) {
			system("cls");
			return;
		}
		else if (mediaList.at(choice - 1) != NULL) {
			//Open up Media interaction menu
			MediaInteractionMenu(mediaList.at(choice - 1));
		}
		else cout << "Invalid Selection, try again" << endl;

		

	} while (true); //MAKE THIS NOT A WHILE TRUE
}

void InventoryScreen::MediaInteractionMenu(LibraryMedia* selectedMedia) {
	system("cls");

	int choice;
	bool goBack = false;
	do
	{
		cout << "Selected Media";
		selectedMedia->ToString();
		cout << setfill('-') << setw(115) << "" << endl;
		cout << setfill('-') << setw(115) << "" << endl;
		cout << setfill('-') << setw(116) << "\n" << endl;
		cout << setfill(' ') << setw(68) << "What would you like to do?\n" << endl;

		if (selectedMedia->GetInventoryCount() > 0) {
			cout << setfill(' ') << setw(54) << "1. Add to cart " << endl; //FIXME: Make this buy if they are guest, if they are no copies and they are guest then print 
		}
		else {
			//if() //Check if user is a borrower, if not then they can't call for media and it should say media is out of stock
			cout << "1. Call For Media" << endl; //Not sure if a guest should be able to call for media
		}
		//if(isAdmin) {
		//FIXME:: Only print these options if current user is admin
		cout << setfill(' ') << setw(53) << "2. Update Media" << endl;
		cout << setfill(' ') << setw(56) << "3. Delete Media" << endl;
		//END ADMIN SECTION
		//}
		cout << setfill(' ') << setw(51) << "0. Return\n" << endl;
		cout << setfill(' ') << setw(58) << "Enter Your Choice:\t";


		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> choice;
		if (!cin) continue;
		switch (choice) {
		case 0:
			goBack = true;
			break;
		case 1:
			//if(!isGuest){
			//FIXME:: If normal user add to cart, unless no inventory then call, if guest only buy
			//MediaID.push_back(selectedMedia.GetMediaID());
			// }
			//else{ // if (isGuest){
			/*MediaPrice.push_back(selectedMedia.GetPrice());
			MediaTitle.push_back(selectedMedia.GetTitle());
			{
				ofstream buyList("PurchaseList.txt", ios::in | ios::out);
				if (!buyList.is_open()) {
					cout << "File not opened successfully" << endl;
				}
				ostream_iterator<string> out_iterator(buyList, "\n");
				copy(MediaTitle.begin(), MediaTitle.end(), out_iterator);
				ostream_iterator<double> output_iterator(buyList, "\n");
				copy(MediaPrice.begin(), MediaPrice.end(), output_iterator);
				buyList.close();
			}
			*/
			break;
		case 2:
			//CHECK IF ADMIN
			//if(CurrentSessionInfo::currUser.ge){
			//	cout << "Invalid choice." << endl;
			//}else{}
			EditMediaDataMenu(selectedMedia);
			break;
		case 3:
			//CHECK IF ADMIN DON'T ALLOW IF NOT ADMIN
			//if(!isAdmin){
			//cout << "Invalid choice." << endl;
			//}else{
			//Delete the media and all associated data
			//}
			break;
		default:
			system("cls");
			cout << "Invalid Input, try again" << endl;
		}

	} while (!goBack);
	
}

void InventoryScreen::ConfirmMediaCheckout() {
	system("cls");
	for (LibraryMedia* media : mediaToCheckoutOrBuy) {
		media->ToString();
		cout << endl;
	}

	int choice;
	do
	{
		cout << "Does this look correct?" << endl;
		cout << "1.Yes" << endl;
		cout << "2.No, clears cart" << endl;
		


		//Show them a preview of their cart
		for (LibraryMedia* media : mediaToCheckoutOrBuy)
		{
			cout << media->GetMediaType() << "---" << media->GetTitle() << endl;
		}
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> choice;
		if (choice == 1) {
			//If user is not a guest
			//Checkout Media
			for (LibraryMedia* media : mediaToCheckoutOrBuy)
			{
				media->ChangeCount(-1); //Removing one from the count
				CheckedoutMedia temp(CurrentSessionInfo::currUser.getLibID(), media->GetMediaID());
				CurrentSessionInfo::borrowedMediaList.push_back(temp);
				delete media; //Delete the pointer after we are done with it
			}
			mediaToCheckoutOrBuy.clear();
		}
		else if (choice == 2) {
			//Clears cart and returns
			//Deletes all pointers and then clears the vector
			for (LibraryMedia* mediaP : mediaToCheckoutOrBuy) {
				delete mediaP;
			}
			mediaToCheckoutOrBuy.clear();
		}
	} while (choice != 1 && choice != 2); //If the user enter numbers other than 1 or 2
}

void InventoryScreen::EditMediaDataMenu(LibraryMedia* selectedMedia) {
	int choice;
	bool goBack = false;
	LibraryMedia::mediaTypes selectedMediaType = selectedMedia->GetMediaType();
	do
	{
		system("cls");
		cout << "Editing: ";
		selectedMedia->ToString();
		cout << endl;

		cout << "0. Return" << endl;
		cout << "1. Change Title" << endl;
		cout << "2. Change Authors" << endl;
		cout << "3. Change Publishers" << endl;
		cout << "4. Change Category" << endl;
		cout << "5. Change SubCateogory" << endl;
		cout << "6. Change Price" << endl;
		cout << "7. Change Doner" << endl;
		cout << "8. Change Iventory Count" << endl;

		switch (selectedMediaType)
		{
		case LibraryMedia::book:
			cout << "9. Change Edition" << endl;
			cout << "10. Change ISBN" << endl;
			break;
		case LibraryMedia::conferenceJournal:
			cout << "9. Change Date Of Conference" << endl;
			cout << "10. Change Place Of Conference" << endl;
			break;
		case LibraryMedia::newspaper:
			cout << "9. Change Publish Rate" << endl;
			break;
		case LibraryMedia::periodical:
			cout << "9. Change Publish Rate" << endl;
			break;
		default:
			break;
		}
		cout << "Enter Your Choice: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> choice;

		if (!cin) continue;
		//Using a if else block instead of a switch statment so we can dymamically cast inside the else if blocks
		if (choice == 0) goBack = true;
		else if (choice == 1) selectedMedia->SetTitle();
		else if (choice == 2) selectedMedia->SetAuthors();
		else if (choice == 3) selectedMedia->SetPublishers();
		else if (choice == 4) selectedMedia->SetCategory();
		else if (choice == 5) selectedMedia->SetSubCategory();
		else if (choice == 6) selectedMedia->SetPrice();
		else if (choice == 7) selectedMedia->SetDoner();
		else if (choice == 8) selectedMedia->SetInventoryCount();
		else if (choice == 9) {
			if (selectedMediaType == LibraryMedia::book) {
				dynamic_cast<Book*>(selectedMedia)->SetEdition();
			}
			else if (selectedMediaType == LibraryMedia::newspaper) {
				dynamic_cast<Newspaper*>(selectedMedia)->SetPublishRate();
			}			
			else if (selectedMediaType == LibraryMedia::conferenceJournal) {
				dynamic_cast<ConferenceJournal*>(selectedMedia)->SetDateOfConference();
			}
			else if (selectedMediaType == LibraryMedia::periodical) {
				dynamic_cast<Periodical*>(selectedMedia)->SetPublishRate();
			}
		}
		else if (choice == 10) {
			if (selectedMediaType == LibraryMedia::book) {
				dynamic_cast<Book*>(selectedMedia)->SetISBN();
			}
			else if (selectedMediaType == LibraryMedia::conferenceJournal) {
				dynamic_cast<ConferenceJournal*>(selectedMedia)->SetPlaceOfConference();
			}
			else {//If users selectes 10 and the media is not either of the two above its an error
				system("cls");
				cout << "Invalid input, try again" << endl;
			}
		}
		else { //If user does not select a number from 0 to 10, tell them its invalid inputt
			system("cls");
			cout << "Invalid input, try again" << endl;
		}
	} while (!goBack);
	//SelectedMedia pointer might need to be deleted
}
#endif // !INVENTORYSCREEN_CPP