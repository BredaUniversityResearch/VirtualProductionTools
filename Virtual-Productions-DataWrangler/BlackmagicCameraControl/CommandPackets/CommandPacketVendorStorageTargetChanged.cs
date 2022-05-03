﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BlackmagicCameraControl.CommandPackets
{
	[CommandPacketMeta(12, 0, 2, ECommandDataType.Int16)]
	public class CommandPacketVendorStorageTargetChanged: ICommandPacketBase
	{
		public short StorageDriveIdentifier;	//
		public string StorageTargetName => $"A{StorageDriveIdentifier:D3}";

		public CommandPacketVendorStorageTargetChanged(CommandReader a_reader)
		{
			StorageDriveIdentifier = a_reader.ReadInt16();
		}

		public override void WriteTo(CommandWriter a_writer)
		{
			a_writer.Write(StorageDriveIdentifier);
		}
	}
}
