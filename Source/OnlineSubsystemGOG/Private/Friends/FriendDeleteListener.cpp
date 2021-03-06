#include "FriendDeleteListener.h"

#include "OnlineFriendsGOG.h"

FFriendDeleteListener::FFriendDeleteListener(
	FOnlineFriendsGOG& InFriendsInterface,
	const FUniqueNetId& InFriendId,
	FString InListName)
	: friendsInterface{InFriendsInterface}
	, friendId{InFriendId}
	, listName{MoveTemp(InListName)}
{
}

void FFriendDeleteListener::OnFriendDeleteSuccess(galaxy::api::GalaxyID InUserID)
{
	UE_LOG_ONLINE_FRIEND(Display, TEXT("FFriendDeleteListener::OnFriendDeleteSuccess()"));
	TriggerOnDeleteFriendCompleteDelegates(true);
}

void FFriendDeleteListener::OnFriendDeleteFailure(galaxy::api::GalaxyID InUserID, galaxy::api::IFriendDeleteListener::FailureReason InFailureReason)
{
	UE_LOG_ONLINE_FRIEND(Warning, TEXT("FFriendDeleteListener::OnFriendDeleteFailure()"));
	TriggerOnDeleteFriendCompleteDelegates(false, TEXT("Undefined error"));
}

void FFriendDeleteListener::TriggerOnDeleteFriendCompleteDelegates(bool InWasSuccessful, FString InErrorMessage)
{
	friendsInterface.TriggerOnDeleteFriendCompleteDelegates(LOCAL_USER_NUM, InWasSuccessful, MoveTemp(friendId), MoveTemp(listName), MoveTemp(InErrorMessage));
	friendsInterface.FreeListener(MoveTemp(ListenerID));
}
