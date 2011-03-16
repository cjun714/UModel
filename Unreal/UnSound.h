#ifndef __UNSOUND_H__
#define __UNSOUND_H__


class USound : public UObject
{
	DECLARE_CLASS(USound, UObject);
public:
	float				f2C;
	FName				f5C;
	TLazyArray<byte>	RawData;

	void Serialize(FArchive &Ar)
	{
		guard(USound::Serialize);

		Super::Serialize(Ar);
		Ar << f5C;
#if UT2
		if (Ar.Game == GAME_UT2 && Ar.ArLicenseeVer >= 2) Ar << f2C;
#endif
		Ar << RawData;

		unguard;
	}
};


#if UNREAL3

class USoundNodeWave : public UObject
{
	DECLARE_CLASS(USoundNodeWave, UObject);
public:
	FByteBulkData		RawData;
	FByteBulkData		CompressedPCData;
	FByteBulkData		CompressedXbox360Data;
	FByteBulkData		CompressedPS3Data;

	void Serialize(FArchive &Ar)
	{
		guard(USoundNodeWave::Serialize);

		Super::Serialize(Ar);
		RawData.Serialize(Ar);
		CompressedPCData.Serialize(Ar);
		CompressedXbox360Data.Serialize(Ar);
		CompressedPS3Data.Serialize(Ar);
#if 0
		printf("Sound: raw(%d) pc(%d) xbox(%d) ps3(%d)\n",
			RawData.ElementCount,
			CompressedPCData.ElementCount,
			CompressedXbox360Data.ElementCount,
			CompressedPS3Data.ElementCount
		);
#endif

		unguard;
	}
};

#endif // UNREAL3


#define REGISTER_SOUND_CLASSES		\
	REGISTER_CLASS(USound)

#define REGISTER_SOUND_CLASSES_UE3	\
	REGISTER_CLASS(USoundNodeWave)

#endif // __UNSOUND_H__
