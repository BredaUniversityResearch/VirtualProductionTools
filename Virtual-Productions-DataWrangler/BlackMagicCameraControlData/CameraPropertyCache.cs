﻿using BlackmagicCameraControlData.CommandPackets;

namespace BlackmagicCameraControlData
{
	//Caches all camera properties, and dispatches event when data has changed.
	public class CameraPropertyCache
	{
		private readonly Dictionary<CommandIdentifier, ICommandPacketBase> m_currentValues = new Dictionary<CommandIdentifier, ICommandPacketBase>();

		public bool CheckPropertyChanged(ICommandPacketBase a_packet)
		{
			return CheckPropertyChanged(CommandIdentifier.FromInstance(a_packet), a_packet);
		}

		public bool CheckPropertyChanged(CommandIdentifier a_identifier, ICommandPacketBase a_packet)
		{
			bool wasChanged = false;
			if (m_currentValues.TryGetValue(a_identifier, out ICommandPacketBase? existingValue))
			{
				if (!existingValue.Equals(a_packet))
				{
					m_currentValues[a_identifier] = a_packet;
					wasChanged = true;
				}
			}
			else
			{
				m_currentValues.Add(a_identifier, a_packet);
				wasChanged = true;
			}

			return wasChanged;
		}
	}
}