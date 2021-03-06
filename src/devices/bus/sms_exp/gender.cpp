// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
/**********************************************************************

    Sega Master System "Gender Adapter" emulation

The Gender Adapter is not an official Sega product. It is produced since 2006
by the SMSPower website to permit to plug a cartridge on the expansion slot
on any SMS 1 model. This includes the Japanese SMS, which has FM sound, so
it is a way to get FM music of western cartridges that have FM code but were
not released in Japan. Some games have compatibility issues, confirmed on the
real hardware, when run plugged-in to the SMS expansion slot.

**********************************************************************/

#include "emu.h"
#include "gender.h"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

DEFINE_DEVICE_TYPE(SMS_GENDER_ADAPTER, sms_gender_adapter_device, "sms_gender_adapter", "SMSPower Gender Adapter")



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  sms_gender_adapter_device - constructor
//-------------------------------------------------

sms_gender_adapter_device::sms_gender_adapter_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, SMS_GENDER_ADAPTER, tag, owner, clock),
	device_sms_expansion_slot_interface(mconfig, *this),
	m_subslot(*this, "subslot")
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void sms_gender_adapter_device::device_start()
{
	m_subslot->save_ram();
}


//-------------------------------------------------
// read
//-------------------------------------------------

uint8_t sms_gender_adapter_device::read(offs_t offset)
{
	return m_subslot->read_cart(offset);
}

uint8_t sms_gender_adapter_device::read_ram(offs_t offset)
{
	return m_subslot->read_ram(offset);
}

int sms_gender_adapter_device::get_lphaser_xoffs()
{
	return m_subslot->get_lphaser_xoffs();
}


//-------------------------------------------------
// write
//-------------------------------------------------

void sms_gender_adapter_device::write_mapper(offs_t offset, uint8_t data)
{
	m_subslot->write_mapper(offset, data);
}

void sms_gender_adapter_device::write(offs_t offset, uint8_t data)
{
	m_subslot->write_cart(offset, data);
}

void sms_gender_adapter_device::write_ram(offs_t offset, uint8_t data)
{
	m_subslot->write_ram(offset, data);
}

//-------------------------------------------------
//  device_add_mconfig - add device configuration
//-------------------------------------------------

void sms_gender_adapter_device::device_add_mconfig(machine_config &config)
{
	SMS_CART_SLOT(config, "subslot", sms_cart, nullptr);
}
