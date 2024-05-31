#ifndef LOCALDB_H
#define LOCALDB_H

#include <QSettings>
#include <QVector>
#include <utils/encryption.h>
#include <utils/commondata.h>


class LocalDB
{
public:
    LocalDB();

    // User Config
    static QString getUsername();
    static void setUsername(QString username);

    static QString getPassword();
    static void setPassword(QString password);

    static int getRecentServerID();
    static int getActiveServerID();
    static void setActiveServerID(int ipID);

    static bool isLoggedIn();
    static void setLoggedIn(bool isLoggedIn);

    static QString getFavouritesList();
    static void addFavourite(int ipID);
    static void removeFavourite(int ipID);
    static bool isFavServer(int ipID);

    static int getExpireInDays();
    static void setExpireInDays(int days);

    static QString getValidityDate();
    static void setValidityDate(QString date);

    static QString getExpiryDate();
    static void setExpiryDate(QString date);

    static int getUserType();
    static void setUserType(int type);

    static QString getUserStatus();
    static void setUserStatus(QString status);

    static QString getContactEmail();
    static void setContactEmail(QString email);

    static int getNoticeType();
    static void setNoticeType(int type);

    static QString getNoticeText();
    static void setNoticeText(QString text);

    static double getNoticeStartTime();
    static void setNoticeStartTime(double time);

    static double getNoticeEndTime();
    static void setNoticeEndTime(double time);

    static QString getNoticeLockServerIds();
    static void setNoticeLockServerIds(QString ids);

    static bool isReferenceEnabled();
    static void setReferenceEnabled(bool enabled);

    static bool isFirstLaunch();
    static void setFirstLaunch(bool isFirstLaunch);

    static QString getIPBundle();
    static void setIPBundle(QString list);

    static QString getDeviceInfo();
    static void setDeviceInfo(QString list);

    static QString getSelectedServerFilterTag();
    static void setSelectedServerFiltertag(QString tag);

    // Firestore Config
    static QString getResetTokenVerifyURL();
    static QString getResetURL();
    static QString getForgetURL();
    static void setForgetURL(QString url);

    static QString getTokenVerifyURL();
    static QString getSignUpURL();
    static QString getResendTokenURL();
    static void setSignUpURL(QString url);

    static QString getEmailSubscriptionURL();
    static void setEmailSubscriptionURL(QString url);

    static QString getPaymentURL();
    static void setPaymentURL(QString url);

    static QString getFeedbackSubmitURL();
    static void setFeedbackSubmitURL(QString url);

    static QString getBuyPremiumNote();
    static void setBuyPremiumNote(QString note);

    static QString getReferWithdrawURL();
    static void setReferWithdrawURL(QString url);

    static QString getReferInviteText();
    static void setReferInviteText(QString text);

    static QString getReferStatementURL();
    static void setReferStatementURL(QString url);

    static QString getFeedbackInfoURL();
    static void setFeedbackInfoURL(QString url);

    static QString getReferSubmitURL();
    static void setReferSubmitURL(QString url);

    static QString getDeviceInfoURL();
    static void setDeviceInfoURL(QString url);

    static QString getDeleteAccountURL();
    static void setDeleteAccountURL(QString url);

    static QString getReferRefreshURL();
    static void setReferRefreshURL(QString url);

    static QString getLoginURL();
    static void setLoginURL(QString url);

    static QString getWhatsAppNumbers();
    static void setWhatsAppNumbers(QString numbers);

    static bool isWalletEnabled();
    static void setWalletEnabled(bool enabled);

    static QString getCheckIpURL();
    static void setCheckIpURL(QString url);

    static QString getReferPricing();
    static void setReferPricing(QString pricing);

    static QString getLastOTP();
    static void setLastOTP(QString otp);

    static QString getPublicIPURL();
    static void setPublicIPURL(QString url);

private:

};

#endif // LOCALDB_H
