
(cl:in-package :asdf)

(defsystem "motion-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "eventResult" :depends-on ("_package_eventResult"))
    (:file "_package_eventResult" :depends-on ("_package"))
    (:file "legoFound" :depends-on ("_package_legoFound"))
    (:file "_package_legoFound" :depends-on ("_package"))
    (:file "legoTask" :depends-on ("_package_legoTask"))
    (:file "_package_legoTask" :depends-on ("_package"))
  ))