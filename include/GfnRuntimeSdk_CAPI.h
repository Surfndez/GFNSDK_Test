// ===============================================================================================
//
/* Copyright (c) 2020, NVIDIA CORPORATION. All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   * Neither the name of NVIDIA CORPORATION nor the names of its
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS "AS IS" AND ANY
  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
  PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
  OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */
//
// ===============================================================================================
//
// C API declarations for GFN Runtime SDK
//
// ===============================================================================================
/**
 * @file GfnRuntimeSdk_CAPI.h
 *
 * API definitions
 */
///
/// @mainpage Native Runtime API Reference
///
/// @section introduction Introduction
/// The NVIDIA GFN Runtime SDK provides a set of interfaces to allow game developers and game
/// publishers to interact with parts of the NVIDIA GeForce NOW ecosystem. Integration is provided
/// by various means, from native C interfaces to RESTful Web API calls, depending on the feature
/// of the SDK.
///
/// @image html ecosystem.png
///
/// This document provides details of how to integrate the native APIs of GFN Runtime SDK features
/// into your application and its developer and deployment processes. For more detailed technical
/// information about the architecture, refer to the architecture section later in this document
///
/// @section overview Overview
///
/// @image html architecture.png
///
/// The GFN Runtime SDK provides a dynamic library with API exports as defined in this document,
/// which is distributed with and loaded by the game/application that utilizes the APIs. The loading
/// of this library should be done in a way that validates the authenticity of the binary via checking
/// for a valid digital signature, and that signature is from NVIDIA Corporation.
///
/// The behavior of the APIs depends on the environment the application is running in; either on a
/// client/user system or in the GeForce NOW (GFN) cloud environment. Each API defines which of the
/// environments it is designed to run in.
///
/// On client systems, this library checks for the presence of the GeForce NOW (GFN) client
/// installation when any of the gfnStartStream API variants is called. If the client is not present,
/// then the library will initiate a download and installation of the latest GFN client, presenting UI
/// to the user for the download and installation process. If the GFN client is present, but out of date,
/// then a similar download and install process to update the client will take place before the
/// streaming session will start.
///
/// Once the GFN client is installed, all API actions are deferred to the GFN client. This design allows
/// the dynamic library to stay as thin as possible in the application, and provides backward and forward
/// compatibility to new GFN client packages.
///
/// On GFN game systems, many of the APIs are no-ops as they apply only to client/end-user
/// systems. In those cases, API calls will return a well-defined error code to denote the call
/// was not applicable to the environment.
///
/// NVIDIA provides a backend IDM Service that application developers can use to validate users
/// and obtain user information from.This provides a seamless flow for users to bypass multiple
/// login steps in streaming a game through GFN.
///
/// A simplified flow diagram of how this functions is shown below:
///
/// @image html authentication.png
///
/// Authentication between the Partner IDM and NVIDIA IDM happens using secure
/// HTTPS web API calls, and the account linking flow utilizes standard oauth2
/// protocol. Once the account link is established the authentication process
/// between Partner and NVIDIA becomes transparent to the user, and gaming
/// streaming can be initiated without requiring any further authentication or
/// manual login.
///
/// @image html account_link_flow.png
///
/// After the account link between Partner and NVIDIA has been established, that
/// link can be utilized on the GFN server to facilitate Single Sign-On (SSO) so
/// that the user does not have to manually login again, but all authentication
/// happens transparently and the game launches immediately.
///
/// @image html sso.png
///
/// For additional high-level overview, please refer to the SDK primer available as part of the
/// documentation section of the SDK's repository.
///
/// @section keyconcepts Key Concepts
///
/// GFN Runtime API methods are used to make requests from or to notify the GFN
/// backend.
///
/// When your application is operating outside of the GFN environment, these
/// methods are simple stubs that incur almost no cost, so it's safe to add
/// these to your main build.
///
/// The calling convention differs by which API you've selected to use. In most
/// cases, the methods return a GfnRuntimeError result, which can be used by the
/// application to check for errors. In addition, some methods are asynchronous
/// by nature, but provide synchronous variants when possible.
///
/// @image html sequence.png
///
/// @section apiReference API Reference
/// @subsection general_section General / Common methods
/// @ref general
///
/// Language | API
/// -------- | -------------------------------------
/// C        | @ref gfnInitializeRuntimeSdk
///
/// @copydoc gfnInitializeRuntimeSdk
///
/// Language | API
/// -------- | -------------------------------------
/// C        | @ref gfnShutdownRuntimeSdk
///
/// @copydoc gfnShutdownRuntimeSdk
///
/// @subsection launcher_game_section Launcher or Game Specific Methods
/// @ref launcher
///
/// Language | API
/// -------- | -------------------------------------
/// C        | @ref gfnIsRunningInCloud
///
/// @copydoc gfnIsRunningInCloud
///
/// Language | API
/// -------- | -------------------------------------
/// C        | @ref gfnFree
///
/// @copydoc gfnIsRunningInCloud
///
/// Language | API
/// -------- | -------------------------------------
/// C        | @ref gfnIsTitleAvailable
///
/// @copydoc gfnIsTitleAvailable
///
/// Language | API
/// -------- | -------------------------------------
/// C        | @ref gfnGetTitlesAvailable
///
/// @copydoc gfnGetTitlesAvailable
///
/// Language | API
/// -------- | -------------------------------------
/// C sync   | @ref gfnSetupTitle
///
/// @copydoc gfnSetupTitle
///
/// Language | API
/// -------- | -------------------------------------
/// C sync   | @ref gfnTitleExited
///
/// @copydoc gfnTitleExited
///
/// Language | API
/// -------- | -------------------------------------
/// C        | @ref gfnGetClientIp
///
/// @copydoc gfnGetClientIp
///
/// Language | API
/// -------- | -------------------------------------
/// C        | @ref gfnGetClientLanguageCode
///
/// @copydoc gfnGetClientLanguageCode
///
/// Language | API
/// -------- | -------------------------------------
/// C        | @ref gfnGetClientCountryCode
///
/// @copydoc gfnGetClientCountryCode
///
/// Language | API
/// -------- | -------------------------------------
/// C        | @ref gfnStartStream
///
/// @copydoc gfnStartStream
///
/// Language | API
/// -------- | -------------------------------------
/// C        | @ref gfnStartStreamAsync
///
/// @copydoc gfnStartStreamAsync
///
/// Language | API
/// -------- | -------------------------------------
/// C        | @ref gfnStopStream
///
/// @copydoc gfnStopStream
///
/// Language | API
/// -------- | -------------------------------------
/// C        | @ref gfnStopStreamAsync
///
/// @copydoc gfnStopStreamAsync
///
/// Language | API
/// -------- | -------------------------------------
/// C        | @ref gfnGetCustomData
///
/// @copydoc gfnGetCustomData
///
/// @subsection callback_section Callback-related Methods
/// @ref callbacks
///
/// Language | API
/// -------- | -------------------------------------
/// C        | @ref gfnRegisterExitCallback
///
/// @copydoc gfnRegisterExitCallback
///
/// Language | API
/// -------- | -------------------------------------
/// C        | @ref gfnRegisterPauseCallback
///
/// @copydoc gfnRegisterPauseCallback
///
/// Language | API
/// -------- | -------------------------------------
/// C        | @ref gfnRegisterInstallCallback
///
/// @copydoc gfnRegisterInstallCallback
///
/// Language | API
/// -------- | -------------------------------------
/// C        | @ref gfnRegisterStreamStatusCallback
///
/// @copydoc gfnRegisterStreamStatusCallback
///

#ifndef GFN_RUNTIME_SDK_CAPI_H
#define GFN_RUNTIME_SDK_CAPI_H

// Required for streamer / DLL download step in StartStream
#ifdef _WIN32
#   pragma comment(lib, "ws2_32.lib")
#   pragma comment(lib, "crypt32.lib")
#   pragma comment(lib, "Wldap32.lib")
#   pragma comment(lib, "version.lib")
#   pragma comment(lib, "wintrust")
#   define GFN_CALLBACK __stdcall
#   define NVGFNSDK_EXPORT __declspec(dllexport)
#   define NVGFNSDKApi __cdecl
#else
// Support to be added in a later release
/// Future support
#   define GFN_CALLBACK
/// Future support
#   define NVGFNSDK_EXPORT
/// Future support
#   define NVGFNSDKApi
#endif

#include <stddef.h>
#include <stdint.h>

#ifndef __cplusplus
/// Simple aliasing for bool support
typedef char bool;
/// Simple aliasing for Boolean false
#define false 0
/// Simple aliasing for Boolean true
#define true 1
#endif

/// Version of the GeForce NOW SDK
#define GFN_RUNTIME_SDK_VERSION 1.4

/// One of the possible values of AuthType_t. Delegate token provided by NVIDIA IDM
#define AUTH_NVIDIA_DEFAULT 7
/// One of the possible values of AuthType_t. JSON Web Token
#define AUTH_NVIDIA_JWT 8

#ifdef __cplusplus
    extern "C"
    {
#endif
        // ============================================================================================
        // Constants/Enums
        // ============================================================================================

        /// @brief Returned by InitializeGfnRuntime and GfnRuntime API methods
        typedef enum GfnRuntimeError
        {
            gfnSuccess =                  0,
            gfnInitSuccessClientOnly =    1, ///< SDK initialized, but only cloud independent functionality available (such as gfnStartStream).
            gfnInitFailure           =   -1, ///< SDK initialization failure for any reason other than memory allocation failure.
            gfnDllNotPresent =           -2,
            gfnComError =                -3, ///< Geforce NOW SDK internal component communication error.
            gfnLibraryCallFailure =      -4, ///< Geforce NOW SDK components were reachable, but could not serve the request.
            gfnIncompatibleVersion =     -5,
            gfnUnableToAllocateMemory =  -6,
            gfnInvalidParameter =        -7,
            gfnInternalError =           -8, ///< Generic Geforce NOW SDK internal error.
            gfnUnsupportedAPICall =      -9,
            gfnInvalidToken =            -10,
            gfnTimedOut =                -11,
            gfnSetupTitleFailure =       -12,
            gfnClientDownloadFailed =    -13, ///< Failed to download the Geforce NOW client.
            gfnCallWrongEnvironment =    -14, ///< Function limited to specific environment called in wrong environment
            gfnWebApiFailed          =   -15, ///< A call to a NVIDIA Web API failed to return valid data
            gfnStreamFailure =           -16, ///< GeForceNOW Streamer hit a failure while starting a stream
            gfnAPINotFound =             -17, ///< Library API call not found
            gfnAPINotInit =              -18, ///< API not initialized
            gfnStreamStopFailure =       -19, ///< Failed to stop active streaming session
            gfnUnhandledException =      -20, ///< Unhandled exceptions
            gfnIPCFailure =              -21, ///< Messagebus IPC failures
            gfnCanceled =                -22, ///< Activity was canceled, for example, user canceled the download of GFN client
        } GfnRuntimeError;

        ///
        /// @par Description
        /// GfnRuntimeError success function
        ///
        /// @par Usage
        /// Use to determine if GfnRuntimeError value translates to success
        ///
        /// @param r      - GfnRuntimeError type value
        ///
        /// @retval true  - GfnRuntimeError value indicates success
        /// @retval false - GfnRuntimeError value indicates failure
        inline bool GFNSDK_SUCCEEDED(GfnRuntimeError r)
        {
            return r >= 0;
        }

        ///
        /// @par Description
        /// GfnRuntimeError failure function
        ///
        /// @par Usage
        /// Use to determine if GfnRuntimeError value translates to failure
        ///
        /// @param r      - GfnRuntimeError type value
        ///
        /// @retval true  - GfnRuntimeError value indicates failure
        /// @retval false - GfnRuntimeError value indicates success
        inline bool GFNSDK_FAILED(GfnRuntimeError r)
        {
            return r < 0;
        }

        /// @brief Values for languages supported by the GFN SDK, used to define which language any SDK dialogs should be displayed in.
        typedef enum GfnDisplayLanguage
        {
            gfnDefaultLanguage = 0,         /// Uses the default system language
            gfn_bg_BG = 1,
            gfn_cs_CZ = 2,
            gfn_nl_NL = 3,
            gfn_de_DE = 4,
            gfn_el_GR = 5,
            gfn_en_US = 6,
            gfn_en_UK = 7,
            gfn_es_ES = 8,
            gfn_es_MX = 9,
            gfn_fi_FI = 10,
            gfn_fr_FR = 11,
            gfn_hu_HU = 12,
            gfn_it_IT = 13,
            gfn_ja_JP = 14,
            gfn_ko_KR = 15,
            gfn_nb_NO = 16,
            gfn_po_PO = 17,
            gfn_pt_BR = 18,
            gfn_pt_PT = 19,
            gfn_ro_RO = 20,
            gfn_ru_RU = 21,
            gfn_sv_SE = 22,
            gfn_th_TH = 23,
            gfn_tr_TR = 24,
            gfn_uk_UA = 25,
            gfn_zh_CN = 26,
            gfn_zh_TW = 27,
            gfn_en_GB = 28,
            gfn_hr_HR = 29,
            gfn_sk_SK = 30,
            gfn_sl_SI = 31,
            gfn_da_DK = 32,
            gfnMaxLanguage = gfn_da_DK
        } GfnDisplayLanguage;

        /** @brief Returned by callbacks the application registers with the Geforce NOW Runtime SDK, or passes
         *  in to asynchronous SDK calls.
         */
        typedef enum GfnApplicationCallbackResult
        {
            crCallbackSuccess =  0, ///< Return to indicate that a callback has performed the requested operation
            crCallbackFailure = -1  ///< Return to indicate that a callback did not perform the requested operation
        } GfnApplicationCallbackResult;

        /// @brief Output response when streaming has started
        typedef struct StartStreamResponse
        {
            bool downloaded; ///< True if Geforce NOW client components were downloaded from the release site.
        } StartStreamResponse;

        /// @brief Callback function signation for notifications on status of starting a streaming session.
        typedef void(GFN_CALLBACK *StartStreamCallbackSig)(GfnRuntimeError, StartStreamResponse*, void* context);

        /// @brief Callback function signation for notifications on status of stop a streaming session.
        typedef void(GFN_CALLBACK* StopStreamCallbackSig)(GfnRuntimeError, void* context);

        /// @brief Type of token to use for GFN session. Valid values include AUTH_NVIDIA_DEFAULT and AUTH_NVIDIA_JWT.
        typedef unsigned int AuthType_t;

        /// @brief Input data for gfnStartStream
        typedef struct StartStreamInput
        {
            unsigned int uiTitleId;     ///< GFN-sourced game-specific unique identifier.
            const char* pchAuthToken;   ///< NVIDIA IDM Token string
            AuthType_t tokenType;       ///< Token identifier
            const char* pchCustomData;  ///< Optional data that is passed to the streaming cloud instance and can be retrieved in that instance of application.
            const char* pchCustomAuth;  ///< Optional client-specific token data that should be used to authenticate the user on the game seat for SSO purposes.
        } StartStreamInput;

        /// @brief Input to the function registered via gfnRegisterInstallCallback (if any).
        typedef struct TitleInstallationInformation
        {
            const char* pchPlatformAppId; ///< Platform application ID passed into the API.
            const char* pchBuildPath;     ///< The path at which game build files can be found.
            const char* pchMetadataPath;  ///< Optionally contains the path at which game metadata can be found, else NULL.
        } TitleInstallationInformation;

        /// @brief Possible states of the client streamer
        typedef enum GfnStreamStatus
        {
            GfnStreamStatusInit,           ///< Initial default state
            GfnStreamStatusNetworkTest,    ///< Client is running a network test to determine the best zone
            GfnStreamStatusLoading,        ///< Client is loading the game
            GfnStreamStatusStreaming,      ///< Client is actively streaming
            GfnStreamStatusDone,           ///< Client has successfully finished streaming
            GfnStreamStatusError,          ///< Client has stopped streaming and has entered an error state
            GfnStreamStatusGotInputFocus,  ///< Client has gained input focus to the streamer window
            GfnStreamStatusLostInputFocus  ///< Client has lost input focus to the streamer window
        } GfnStreamStatus;

        /// @brief Converts a GfnStreamStatus enum to a human-readable string
        inline const char* GfnStreamStatusToString(GfnStreamStatus status)
        {
            switch (status)
            {
            case GfnStreamStatusInit:           return "Init";
            case GfnStreamStatusNetworkTest:    return "NetworkTest";
            case GfnStreamStatusLoading:        return "Loading";
            case GfnStreamStatusStreaming:      return "Streaming";
            case GfnStreamStatusDone:           return "Done";
            case GfnStreamStatusError:          return "Error";
            case GfnStreamStatusGotInputFocus:  return "GotInputFocus";
            case GfnStreamStatusLostInputFocus: return "LostInputFocus";
            }
            return "Unknown GfnStreamStatus";
        }

        // ============================================================================================
        // Callback signatures
        // ============================================================================================

        // Callbacks that client code should implement and register via the appropriate callback
        // registration function (listed as part of the C API below).
        /// @brief Callback function for notification when a game should exit. Register via gfnRegisterExitCallback API.
        typedef GfnApplicationCallbackResult(GFN_CALLBACK *ExitCallbackSig)(void* pUserContext);
        /// @brief Callback function for notification when a game should pause. Register via gfnRegisterPauseCallback API.
        typedef GfnApplicationCallbackResult(GFN_CALLBACK *PauseCallbackSig)(void* pUserContext);
        /// @brief Callback function for notification when a game is being installed to allow for installation actions. Register via gfnRegisterInstallCallback API.
        typedef GfnApplicationCallbackResult(GFN_CALLBACK *InstallCallbackSig)(const TitleInstallationInformation* pInfo, void* pUserContext);
        /// @brief Callback function for notifications on status of starting a streaming session. Register via gfnRegisterStreamStatusCallback API.
        typedef GfnApplicationCallbackResult(GFN_CALLBACK *StreamStatusCallbackSig)(GfnStreamStatus status, void* pUserContext);
        /// @brief Callback function for notifications when a game should save its state. Register via gfnRegisterSaveCallback API.
        typedef GfnApplicationCallbackResult(GFN_CALLBACK* SaveCallbackSig)(void* pUserContext);

        // ============================================================================================
        // C API
        // ============================================================================================

        // ============================================================================================
        // SDK Initialization / Shutdown

        /// @defgroup general General / Common Methods
        /// The functions contained in this section control the lifecycle of the SDK.
        /// @{

        /// @par Description
        /// Should be called at application startup and prior to any other GFN Runtime API methods.
        /// The SDK features which become available as a result of initializing the Geforce NOW
        /// SDK are dependent on the type of environment in which the SDK operates (client or cloud).
        ///
        /// @par Environment
        /// Cloud and Client
        ///
        /// @par Usage
        /// Call as soon as possible during application startup.
        ///
        /// @param displayLanguage            - Language to use for any UI, such as GFN download and install progress dialogs.
        ///                                     Defaults to system language if not defined.
        /// @retval gfnSuccess                - If the SDK was initialized and all SDK features are available.
        /// @retval gfnInitSuccessClientOnly  - If the SDK was initialized, but only client-side functionality is available, such as
        ///                                     calls to gfnStartStream. By definition, gfnIsRunningInCloud is expected to return false
        ///                                     in this scenario.
        /// @retval gfnUnableToAllocateMemory - SDK initialization failed due to lack of available memory, and no SDK functionality is
        ///                                     available.
        /// @retval gfnInitFailure            - SDK initialization failed for any other reason, and no SDK functionality is available.
        NVGFNSDK_EXPORT GfnRuntimeError NVGFNSDKApi gfnInitializeRuntimeSdk(GfnDisplayLanguage displayLanguage);

        ///
        /// @par Description
        /// Releases the SDK, and frees up memory allocated by GFN and disconnects from GFN backend.
        ///
        /// @par Environment
        /// Cloud and Client
        ///
        /// @par Usage
        /// Call during application shutdown or when GFN Runtime API methods are no longer needed.
        NVGFNSDK_EXPORT void NVGFNSDKApi gfnShutdownRuntimeSdk();
        /// @}

        /// @defgroup callbacks Client Callback Registration
        /// Callback registration functions to receieve various messages / requests from the SDK.
        /// Register only after calling gfnInitializeRuntimeSdk().
        /// @{

        ///
        /// @par Description
        /// Register an application function to call when Geforce NOW needs to exit the game.
        ///
        /// @par Environment
        /// Cloud
        ///
        /// @par Usage
        /// Register an application function to call when Geforce NOW needs to exit the game.
        ///
        /// @param exitCallback             - Function pointer to application code to call when Geforce NOW
        ///                                   needs to exit the game.
        /// @param pUserContext             - Pointer to user context, which will be passed unmodified to the
        ///                                   registered callback. Can be NULL.
        ///
        /// @retval gfnSuccess              - On success, when running in a Geforce NOW environment
        /// @retval gfnDLLNotPresent        - If callback could not be registered
        /// @retval gfnInvalidParameter     - If exitCallback function pointer is NULL.
        /// @retval gfnCallWrongEnvironment - If callback could not be registered since this function
        ///                                   was called outside of a cloud execution environment
        NVGFNSDK_EXPORT GfnRuntimeError NVGFNSDKApi gfnRegisterExitCallback(ExitCallbackSig exitCallback, void* pUserContext);

        ///
        /// @par Description
        /// Register an application callback with Geforce NOW to be called when Geforce NOW
        /// needs to pause the game on the user's behalf. For Multiplayer games, it is
        /// recommended that this is implemented similar to a client disconnect.
        ///
        /// @par Environment
        /// Cloud
        ///
        /// @par Usage
        /// Register an application function to call when Geforce NOW needs to pause the game.
        ///
        /// @param pauseCallback            - Function pointer to application code to call when
        ///                                   Geforce NOW needs to pause the game
        /// @param pUserContext             - Pointer to user context, which will be passed unmodified to the
        ///                                   registered callback. Can be NULL.
        ///
        /// @retval gfnSuccess              - On success, when running in a Geforce NOW environment
        /// @retval gfnDLLNotPresent        - If callback could not be registered
        /// @retval gfnInvalidParameter     - If pauseCallback function pointer is NULL.
        /// @retval gfnCallWrongEnvironment - If callback could not be registered since this function
        ///                                   was called outside of a cloud execution environment
        NVGFNSDK_EXPORT GfnRuntimeError NVGFNSDKApi gfnRegisterPauseCallback(PauseCallbackSig pauseCallback, void* pUserContext);

        ///
        /// @par Description
        /// Register an application callback with Geforce NOW to be called after a successful call to
        /// @ref gfnSetupTitle. Typically, the callback would handle any additional installation steps that
        /// are necessary after Geforce NOW performs its own setup for a given title.
        ///
        /// @par Environment
        /// Cloud
        ///
        /// @par Usage
        /// Register a function to call after a successful call to gfnSetupTitle.
        ///
        /// @param installCallback            - Function pointer to application code to call after
        ///                                     Geforce NOW successfully performs its own title setup.
        /// @param pUserContext               - Pointer to user context, which will be passed unmodified to the
        ///                                     registered callback. Can be NULL.
        ///
        /// @retval gfnSuccess                - On success, when running in a Geforce NOW environment
        /// @retval gfnDLLNotPresent          - If callback could not be registered
        /// @retval gfnInvalidParameter       - If installCallback function pointer is NULL.
        /// @retval gfnCallWrongEnvironment   - If callback could not be registered since this function
        ///                                   was called outside of a cloud execution environment
        NVGFNSDK_EXPORT GfnRuntimeError NVGFNSDKApi gfnRegisterInstallCallback(InstallCallbackSig installCallback, void* pUserContext);

        ///
        /// @par Description
        /// Register a callback that gets called on the user's PC when the streaming session state changes
        ///
        /// @par Environment
        /// Client
        ///
        /// @par Usage
        /// Register a function to call when stream status changes on the user's client PC
        ///
        /// @param streamStatusCallback         - Function pointer to application code to call after
        ///                                       the Geforce NOW streamer changes state
        /// @param pUserContext                 - Pointer to user context, which will be passed unmodified to the
        ///                                       registered callback. Can be NULL.
        ///
        /// @retval gfnSuccess                  - On success, when running on the client PC
        /// @retval gfnCallWrongEnvironment     - If callback could not be registered since this function
        ///                                       was called outside of a client execution environment
        NVGFNSDK_EXPORT GfnRuntimeError NVGFNSDKApi gfnRegisterStreamStatusCallback(StreamStatusCallbackSig streamStatusCallback, void* pUserContext);
        /// @}

        ///
        /// @par Description
        /// Register an application callback with GFN to be called when GFN needs the application
        /// to save user progress. It is recommended that this be implemented as an autosave if
        /// such a feature is supported by your application.
        ///
        /// @par Usage
        /// Register an application function to call when GFN needs the application to save
        ///
        /// @param saveCallback                 - Function pointer to application code to call when GFN needs
        ///                                       the application to save
        /// @param pUserContext                 - Pointer to user context, which will be passed unmodified to the
        ///                                       callback specified. Can be NULL.
        ///
        /// @retval gfnSuccess                  - On success when running in a GFN environment
        /// @retval gfnDLLNotPresent            - If callback was not registered
        NVGFNSDK_EXPORT GfnRuntimeError NVGFNSDKApi gfnRegisterSaveCallback(SaveCallbackSig saveCallback, void* pUserContext);
        /// @}

        // ============================================================================================
        // Application -> Geforce NOW SDK communication
        // The application should call these methods at the appropriate locations.
        /// @defgroup launcher Launcher Application Methods
        /// The functions is this section are called from a launcher in either the appropriate
        /// cloud or client environment.
        /// @{

        ///
        /// @par Description
        /// Determines if calling application is running in GFN environment or not.
        ///
        /// @par Environment
        /// Cloud and Client
        ///
        /// @par Usage
        /// Use to determine whether to enable / disable any GFN cloud environment specific
        /// application logic, for example, to block any calls to gfnStartStream().
        ///
        /// @retval true                        - Application is running on a GFN game seat virtual machine
        ///                                     in the Geforce NOW cloud.
        /// @retval false                       - Application is not running in the Geforce NOW cloud or in a
        ///                                     Geforce NOW test environment. This value will also be returned if
        ///                                     called before gfnInitializeRuntimeSdk().
        ///
        /// @note
        /// This data is also alternatively accessible in the GFN environment without calling this
        /// API. Please see the "GFN-SDK-ALTERNATIVE-DATA-ACCESS.pdf" document in the "doc" folder
        NVGFNSDK_EXPORT bool NVGFNSDKApi gfnIsRunningInCloud();

        ///
        /// @par Description
        /// Determines if a specific title is available to launch in current streaming session
        ///
        /// @par Environment
        /// Cloud
        ///
        /// @par Usage
        /// Use to determine if a title is available to be streamed from the active GFN cloud instance,
        /// for example, to show a "Play" button in a platform launcher's UI.
        ///
        /// @param pchPlatformAppId - Identifier of the requested title to check
        ///
        /// @retval true                        - Title is available for playing
        /// @retval false                       - Title is not available for playing. The common cases for this is the
        ///                                     title is not supported on GFN, or the GFN servers do not load every
        ///                                     supported game to every system in all cases.
        NVGFNSDK_EXPORT bool NVGFNSDKApi gfnIsTitleAvailable(const char* pchPlatformAppId);

        ///
        /// @par Description
        /// Retrieves all titles that can be launched in the current game streaming session
        ///
        /// @par Environment
        /// Cloud
        ///
        /// @par Usage
        /// Use to retrieve a list of all titles available to launch in the current streaming session,
        /// for example, to add "Play" buttons to all titles instead of calling gfnIsTitleAvailable on
        /// each title.
        ///
        /// @param ppchPlatformAppIds        - Comma-delimited list of platform identifiers. Memory 
        ///                                    is allocated for the list. Call @ref gfnFree to release the memory when done.
        ///
        /// @retval gfnSuccess               - On success
        /// @retval gfnInvalidParameter      - NULL pointer passed in
        /// @retval gfnCallWrongEnvironment  - If called in a client environment
        /// @note
        /// To avoid leaking memory, call @ref gfnFree once done with the list
        NVGFNSDK_EXPORT GfnRuntimeError NVGFNSDKApi gfnGetTitlesAvailable(const char** ppchPlatformAppIds);

        ///
        /// @par Description
        /// Notifies Geforce NOW that an application should be readied for launch. Geforce NOW
        /// will make the build files associated with the application available at the path
        /// returned in the SetupTitleResult struct passed in to the ConfirmTitleSetup callback
        /// provided by the caller. Additionally, Geforce NOW will set all necessary settings to
        /// optimize for the Geforce NOW cloud environment, and download any associated user data,
        /// including save files.
        ///
        /// @par Environment
        /// Cloud
        ///
        /// @par Usage
        /// Use to prepare an application for launch on Geforce NOW, and block on the result.
        ///
        /// @param pchPlatformAppId - Identifier of the requested application to setup
        ///
        /// @retval gfnSuccess               - On success
        /// @retval gfnInvalidParameter      - NULL pointer passed in
        /// @retval gfnCallWrongEnvironment  - If called in a client environment
        /// @retval gfnSetupTitleFailure     - The Geforce NOW SDK failed to set up the title
        /// @return Otherwise, appropriate error code
        NVGFNSDK_EXPORT GfnRuntimeError NVGFNSDKApi gfnSetupTitle(const char* pchPlatformAppId);

        ///
        /// @par Description
        /// Notifies GFN that an application has exited. GFN will then start the
        /// shutdown process for that application. Note that this is for use by
        /// platform clients only and assumes the application has already completed
        /// execution. To shutdown from within an application itself, gfnShutdownRuntimeSDK is used.
        ///
        /// @par Environment
        /// Cloud
        ///
        /// @par Usage
        /// Use to notify GFN that your application has exited.
        ///
        /// @param pchPlatformId             - Identifier of the launcher service, e.g. "Steam"
        /// @param pchPlatformAppId          - Identifier of the application that has exited.
        ///
        /// @retval gfnSuccess               - On success
        /// @retval gfnInvalidParameter      - NULL pointer passed in
        /// @retval gfnCallWrongEnvironment  - If called in a client environment
        /// @return Otherwise, appropriate error code
        NVGFNSDK_EXPORT GfnRuntimeError NVGFNSDKApi gfnTitleExited(const char* pchPlatformId, const char* pchPlatformAppId);

        ///
        /// @par Description
        /// Since applications running under Geforce NOW run in the Geforce NOW data centers,
        /// any IP queries made by the Application will return IPs associated
        /// with the data center, not the user's external client IP, as seen by Internet queries.
        /// This SDK call allows the application to obtain the user's client IP in the IPv4 format
        /// so that developers can make regional business decisions for the user based on it versus
        /// the region of the data center the user is connected to for game streaming sessions.
        ///
        /// @par Environment
        /// Cloud
        ///
        /// @par Usage
        /// Call this during application start or from the platform client in
        /// order to get the user's external client IP address.
        ///
        /// @param ppchClientIp              - Output IPv4 in string format. Example: "192.168.0.1".
        ///                                    Call @ref gfnFree to release the memory when done.
        ///
        /// @retval gfnSuccess               - On success
        /// @retval gfnInvalidParameter      - NULL pointer passed in
        /// @retval gfnCallWrongEnvironment  - If called in a client environment
        /// @return Otherwise, appropriate error code
        /// @note
        /// The IP data returned by this API can be subject to various privacy laws depending on how the
        /// the data is used. To avoid the data being considered Personally Identifiable Information and
        /// subject to those laws, the IP should be used for geolocation lookup only and then discarded.
        /// @note
        /// To avoid leaking memory, call @ref gfnFree once done with the list
        NVGFNSDK_EXPORT GfnRuntimeError NVGFNSDKApi gfnGetClientIp(const char** ppchClientIp);

        ///
        /// @par Description
        /// Gets user's client language code in the form "<lang>-<country>" using
        /// a standard ISO 639-1 language code and ISO 3166-1 Alpha-2 country code.
        ///
        /// @par Environment
        /// Cloud
        ///
        /// @par Usage
        /// Call this during application start or from the platform client in
        /// order to get the user's language and country settings.
        ///
        /// @param ppchLanguageCode          - Language code as a string. Example: "en-US".
        ///                                    Call @ref gfnFree to release the memory when done.
        ///
        /// @retval gfnSuccess               - On success
        /// @retval gfnInvalidParameter      - NULL pointer passed in
        /// @retval gfnCallWrongEnvironment  - If called in a client environment
        /// @return Otherwise, appropriate error code
        /// @note
        /// To avoid leaking memory, call @ref gfnFree once done with the list
        NVGFNSDK_EXPORT GfnRuntimeError NVGFNSDKApi gfnGetClientLanguageCode(const char** ppchLanguageCode);

        ///
        /// @par Description
        /// Gets user’s client country code using ISO 3166-1 Alpha-2 country code.
        ///
        /// @par Environment
        /// Cloud
        ///
        /// @par Usage
        /// Call this during application start or from the platform client in order to get
        /// the user's country code.
        ///
        /// @param pchCountryCode            - Country code as a 2 character string. Example: "US".
        /// @param length                    - Length of pchCountryCode character array, the length
        ///                                    should be at least 3
        ///
        /// @retval gfnSuccess               - On success
        /// @retval gfnInvalidParameter      - NULL pointer passed in or buffer length is too small
        /// @retval gfnCallWrongEnvironment  - If called in a client environment
        /// @return Otherwise, appropriate error code
        NVGFNSDK_EXPORT GfnRuntimeError NVGFNSDKApi gfnGetClientCountryCode(char* pchCountryCode, unsigned int length);

        ///
        /// @par Description
        /// Requests GFN client to start a streamed session of an application in an asynchronous fashion
        ///
        /// @par Environment
        /// Client
        ///
        /// @par Usage
        /// Use to start a streaming session.
        ///
        /// @param pStartStreamInput            - Pointer to a StartStreamInput structure.
        /// @param cb                           - A StartStreamCallbackSig callback to be called with streaming events.
        /// @param context                      - User context
        /// @param timeoutMs                    - Time after which attempt to start streaming will be aborted.
        NVGFNSDK_EXPORT void NVGFNSDKApi gfnStartStreamAsync(const StartStreamInput * pStartStreamInput, StartStreamCallbackSig cb, void* context, unsigned int timeoutMs);

        ///
        /// @par Description
        /// Requests GFN client to start a streamed session of an application in a synchronous (blocking) fashion.
        ///
        /// @par Environment
        /// Client
        ///
        /// @par Usage
        /// Use to start a streaming session.
        ///
        /// @param pStartStreamInput        - Pointer to a StartStreamInput structure.
        /// @param response                 - Start streaming response.
        ///
        /// @retval gfnSuccess              - On success
        /// @retval gfnInvalidParameter     - NULL pointer passed in
        /// @retval gfnCallWrongEnvironment - If called in a cloud environment
        /// @retval gfnStreamFailure        - Network failure or other error prevented the stream from starting
        /// @retval gfnCanceled             - User canceled the download and install of GFN client during stream initialization
        /// @return Otherwise, appropriate error code
        NVGFNSDK_EXPORT GfnRuntimeError NVGFNSDKApi gfnStartStream(StartStreamInput* pStartStreamInput, StartStreamResponse* response);

        ///
        /// @par Description
        /// Requests GFN client to stop the active streaming session of an application in a synchronous (blocking) fashion.
        ///
        /// @par Environment
        /// Client
        ///
        /// @par Usage
        /// Use to request the streaming session be stopped
        ///
        /// @retval gfnSuccess              - On success
        /// @retval gfnStreamStopFailure    - Failure to stop the streaming session
        /// @retval gfnCallWrongEnvironment - If called in a cloud environment
        /// @retval gfnStreamFailure        - Network failure or other error prevented the stream from starting
        /// @return Otherwise, appropriate error code
        NVGFNSDK_EXPORT GfnRuntimeError NVGFNSDKApi gfnStopStream(void);

        ///
        /// @par Description
        /// Requests GFN client to stop the active streaming session of an application in aynchronous fashion.
        ///
        /// @par Environment
        /// Client
        ///
        /// @par Usage
        /// Use to request the streaming session be stopped
        ///
        /// @param cb                           - A StartStreamCallbackSig callback to be called with streaming events.
        /// @param context                      - User context
        /// @param timeoutMs                    - Time after which attempt to stop streaming and associated processed to close will be aborted.
        ///                                       A value of 0 signals to immediately return without waiting for processes to close.
        NVGFNSDK_EXPORT void NVGFNSDKApi gfnStopStreamAsync(StopStreamCallbackSig cb, void* context, unsigned int timeoutMs);

        ///
        /// @par Description
        /// Retrieves custom data passed in by the client in the gfnStartStream call.
        ///
        /// @par Environment
        /// Cloud
        ///
        /// @par Usage
        /// Use during cloud session to retrieve custom data
        ///
        /// @param ppchCustomData            - Populated with the custom data.
        ///                                    Call @ref gfnFree to release the memory when done.
        ///
        /// @retval gfnSuccess               - On success
        /// @retval gfnInvalidParameter      - NULL pointer passed in
        /// @retval gfnCallWrongEnvironment  - If called in a client environment
        /// @return Otherwise, appropriate error code
        /// @note
        /// To avoid leaking memory, call @ref gfnFree once done with the list
        NVGFNSDK_EXPORT GfnRuntimeError NVGFNSDKApi gfnGetCustomData(const char** ppchCustomData);

        ///
        /// @par Description
        /// Retrieves custom authorization data passed in by the client in the gfnStartStream call.
        ///
        /// @par Environment
        /// Cloud
        ///
        /// @par Usage
        /// Use during cloud session to retrieve custom data
        ///
        /// @param ppchAuthData            - Populated with the custom data.
        ///                                  Call @ref gfnFree to release the memory when done.
        ///
        /// @retval gfnSuccess               - On success
        /// @retval gfnInvalidParameter      - NULL pointer passed in
        /// @retval gfnCallWrongEnvironment  - If called in a client environment
        /// @return Otherwise, appropriate error code
        /// @note
        /// To avoid leaking memory, call @ref gfnFree once done with the list
        NVGFNSDK_EXPORT GfnRuntimeError NVGFNSDKApi gfnGetAuthData(const char** ppchAuthData);

        ///
        /// @par Description
        /// Releases memory allocated by Get functions such as, but not limited to, @ref gfnGetAuthData,
        /// @ref gfnGetCustomData, or @ref gfnGetTitlesAvailable
        ///
        /// @par Environment
        /// Cloud
        ///
        /// @par Usage
        /// Use to release memory after a call to a memory-allocated function and you are finished with the data
        ///
        /// @param ppchData                  - Pointer to allocated string memmory
        ///
        /// @retval gfnSuccess               - On success
        /// @retval gfnInvalidParameter      - NULL pointer passed in
        NVGFNSDK_EXPORT GfnRuntimeError NVGFNSDKApi gfnFree(const char** ppchData);
        /// @}

#ifdef __cplusplus
    } // extern "C"
#endif


#endif // GFN_RUNTIME_SDK_CAPI_H
