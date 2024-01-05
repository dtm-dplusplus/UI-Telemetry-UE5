// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToonActivatableWidget.h"
#include "ToonActivatableWidgetStack.h"
#include "ToonLayerWidget.generated.h"

/**
* Struct which stores the layer attributes
* In the future, this can be built out to hold more layer properties
*/
USTRUCT(BlueprintType)
struct FToonLayerData
{
	GENERATED_BODY()

	FToonLayerData()
	{
		LayerID = -1;
		LayerName = "";
	}

	/**
	 * Init Layer data attributes
	 * @param	Name	- The name of the layer, set by the user
	 * @param	ID		- The ID of the layer, set by the subsytem 
	 */
	void InitLayerData(FString Name, const int ID)
	{
		LayerID = ID;
		LayerName = Name;
	}

	/**
	* @return layer's unique ID. Set by the UI Subsytem
	*/
	int GetLayerID() const { return LayerID; }

	/**
	* @return layer's unique name. Set by the UI user
	*/
	FString GetLayerName() const { return LayerName; }

protected:
	/**
	* The layer's Unique ID, set by the UI subsytem.
	*/
	UPROPERTY(BlueprintReadOnly)
	int LayerID;

	/**
	* The layer's Unique name, set by the user.
	* The name is not related to any UMG/CommonUI functionallity.
	* It is soley used by the UI subsystem
	*/
	UPROPERTY(BlueprintReadOnly)
	FString LayerName;

	friend class UToonLayerWidget;
};

/**
 * The Layer Widget allows widgets to be pushed onto a widget stack. Only the top most widget will be activated.
 * When a widget is popped/removed from the top of the stack, the widget beneath it becomes the active widget of the layer
 */
UCLASS()
class TOONTANKS_API UToonLayerWidget : public UToonActivatableWidget
{
	GENERATED_BODY() 

public:
	/**
	* Sets the layer properties.
	* Once activated layer properties cannot be modified.
	* @args Name	- Layer name
	* @args ID		- Layer ID
	*
	*/
	void ActivateLayer(FString Name, const int ID)
	{
		LayerData.LayerName = Name;
		LayerData.LayerID = ID;

		// Create the underlying UMG UWidget. This is neccessary for the widget content to be added to viewport
		GetGameInstance()->GetGameViewportClient()->AddViewportWidgetContent(TakeWidget());
	}

	/**
	 * Deactivate the layer and its widget contents
	 */
	void DeactivateLayer()
	{
		LayerStack->ClearWidgets();

		// Broadcast Underlying UCommonWidget Deactivation
		DeactivateWidget();
		
		// Deactivate Underlying slate widget (Removes all active widgets on layer)
		GetGameInstance()->GetGameViewportClient()->RemoveViewportWidgetContent(TakeWidget());
	}

	/**
	 * @return LayerData struct. Holds layers attributes
	 */
	UFUNCTION(BlueprintCallable)
	FToonLayerData GetLayerData() const { return LayerData; }

	/**
	* @return layer's unique ID. Set by the UI Subsytem
	*/
	UFUNCTION(BlueprintCallable)
	int GetLayerID() const { return LayerData.LayerID; }

	/**
	 * @return layer's unique name. Set by the UI user
	 */
	UFUNCTION(BlueprintCallable)
	FString GetLayerName() const { return LayerData.LayerName; }

	/**
	 * Adds a widget to the layer and activates it.
	 * Acts as a wrapper function to CommonUI AddWidget()
	 * Add a new widget to the layer by pushing it onto the underlying CommonActivatableStack.
	 *
	 * @param	Widget	- The Widget Blueprint to activate
	 */
	UFUNCTION(BlueprintCallable)
	UToonActivatableWidget* PushWidgetToLayer(TSubclassOf<UToonActivatableWidget> Widget);

	/**
	 * Removes the topmost (active) widget from the layer
	 */
	UFUNCTION(BlueprintCallable)
	void RemoveActiveWidget() const
	{
		LayerStack->GetActiveWidget()->DeactivateWidget();
	}

protected:
	/**
	 * Sets the pointer reference value for the stack.
	 * @args UToonActivatableWidgetStack pointer
	 */
	UFUNCTION(BlueprintCallable)
	void SetLayerStack(UToonActivatableWidgetStack* Stack) { LayerStack = Stack; }

private:
	/**
	 * Struct Container which holds the layer's attributes
	 * E.g. LayerID or LayerName
	 */
	FToonLayerData LayerData;

	/**
	* The derived commonUI widget stack onto which widgets are added
	* This is refernce is set in blueprint in UILayer Initialize Event
	*/
	TObjectPtr<UToonActivatableWidgetStack> LayerStack;

};
