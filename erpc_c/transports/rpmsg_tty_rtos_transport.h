/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _EMBEDDED_RPC__RPMSG_LITE_TTY_RTOS_TRANSPORT_H_
#define _EMBEDDED_RPC__RPMSG_LITE_TTY_RTOS_TRANSPORT_H_

#include "crc16.h"
#include "message_buffer.h"
#include "rpmsg_lite.h"
#include "rpmsg_lite_base_transport.h"
#include "rpmsg_ns.h"
#include "rpmsg_queue.h"

/*!
 * @addtogroup rpmsg_tty_rtos_transport
 * @{
 * @file
 */

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Classes
////////////////////////////////////////////////////////////////////////////////

namespace erpc {
/*!
 * @brief Transport that uses RPMsg zero copy RTOS API for interprocessor
 * messaging.
 *
 * @ingroup rpmsg_lite_rtos_transport
 */
class RPMsgTTYRTOSTransport : public RPMsgBaseTransport
{
public:
    /*!
     * @brief Constructor.
     *
     * This function initializes object attributes.
     */
    RPMsgTTYRTOSTransport();

    /*!
     * @brief RPMsgRTOSTransport destructor
     */
    virtual ~RPMsgTTYRTOSTransport();

    /*!
     * @brief This function call RPMsg rtos init function - as RPMsg master
     *
     * @param[in] src_addr Source address.
     * @param[in] dst_addr Destination address.
     * @param[in] base_address RPMsg base address in the shared memory.
     * @param[in] length RPMsg shared memory region length.
     * @param[in] rpmsg_link_id Selection between what cores the communication
     * will occur.
     *
     * @retval kErpcStatus_Success When rpmsg init function was executed
     * successfully.
     * @retval kErpcStatus_InitFailed When rpmsg init function wasn't executed
     * successfully.
     */
    virtual erpc_status_t init(unsigned long src_addr, unsigned long dst_addr, void *base_address, unsigned long length, int rpmsg_link_id);

    /*!
     * @brief This function call RPMsg rtos init function - as RPMsg remote
     *
     * @param[in] src_addr Source address.
     * @param[in] dst_addr Destination address.
     * @param[in] base_address RPMsg base address in the shared memory.
     * @param[in] rpmsg_link_id Selection between what cores the communication
     * will occur.
     * @param[in] ready_cb Callback called after RPMsg init is done and the core
     * is ready.
     *
     * @retval kErpcStatus_Success When rpmsg init function was executed
     * successfully.
     * @retval kErpcStatus_InitFailed When rpmsg init function wasn't executed
     * successfully.
     */
    virtual erpc_status_t init(unsigned long src_addr, unsigned long dst_addr, void *base_address, int rpmsg_link_id, void (*ready_cb)(void), char *nameservice_name);

    /*!
     * @brief Store incoming message to message buffer.
     *
     * In loop while no message come.
     *
     * @param[in] message Message buffer, to which will be stored incoming
     * message.
     *
     * @retval kErpcStatus_ReceiveFailed Failed to receive message buffer.
     * @retval kErpcStatus_Success Successfully received all data.
     */
    virtual erpc_status_t receive(MessageBuffer *message);

    /*!
     * @brief Function to send prepared message.
     *
     * @param[in] message Pass message buffer to send.
     *
     * @retval kErpcStatus_SendFailed Failed to send message buffer.
     * @retval kErpcStatus_Success Successfully sent all data.
     */
    virtual erpc_status_t send(MessageBuffer *message);

    /*!
     * @brief This functions sets thre CRC-16 implementation.
     *
     * @param[in] crcImpl Object containing crc-16 compute function.
     */
    virtual void setCrc16(Crc16 *crcImpl);

protected:
    unsigned long m_dst_addr;                /*!< Destination address used by rpmsg. */
    rpmsg_queue_handle m_rpmsg_queue;        /*!< Handle of RPMsg queue. */
    struct rpmsg_lite_endpoint *m_rpmsg_ept; /*!< Pointer to RPMsg Lite Endpoint structure. */
    Crc16 *m_crcImpl;                        //!< CRC object.
};

} // namespace erpc

/*! @} */

#endif // _EMBEDDED_RPC__RPMSG_LITE_TTY_RTOS_TRANSPORT_H_
