#include "E_AnimDrone.generated.h"

UENUM(BlueprintType)
enum class E_AnimDrone : uint8
{
	Idle UMETA(DisplayName = "Простой"),
	Forward UMETA(DisplayName = "Вперед"),
	Backward UMETA(DisplayName = "Назад"),
	Right UMETA(DisplayName = "Вправо"),
	Left UMETA(DisplayName = "Влево")
};
