
(cl:in-package :asdf)

(defsystem "pre_processer-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "OneChannelDataset" :depends-on ("_package_OneChannelDataset"))
    (:file "_package_OneChannelDataset" :depends-on ("_package"))
  ))