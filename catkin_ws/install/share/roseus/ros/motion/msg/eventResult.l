;; Auto-generated. Do not edit!


(when (boundp 'motion::eventResult)
  (if (not (find-package "MOTION"))
    (make-package "MOTION"))
  (shadow 'eventResult (find-package "MOTION")))
(unless (find-package "MOTION::EVENTRESULT")
  (make-package "MOTION::EVENTRESULT"))

(in-package "ROS")
;;//! \htmlinclude eventResult.msg.html


(defclass motion::eventResult
  :super ros::object
  :slots (_event_id _result_id _authkey ))

(defmethod motion::eventResult
  (:init
   (&key
    ((:event_id __event_id) 0)
    ((:result_id __result_id) 0)
    ((:authkey __authkey) 0)
    )
   (send-super :init)
   (setq _event_id (round __event_id))
   (setq _result_id (round __result_id))
   (setq _authkey (round __authkey))
   self)
  (:event_id
   (&optional __event_id)
   (if __event_id (setq _event_id __event_id)) _event_id)
  (:result_id
   (&optional __result_id)
   (if __result_id (setq _result_id __result_id)) _result_id)
  (:authkey
   (&optional __authkey)
   (if __authkey (setq _authkey __authkey)) _authkey)
  (:serialization-length
   ()
   (+
    ;; int32 _event_id
    4
    ;; int32 _result_id
    4
    ;; int32 _authkey
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _event_id
       (write-long _event_id s)
     ;; int32 _result_id
       (write-long _result_id s)
     ;; int32 _authkey
       (write-long _authkey s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _event_id
     (setq _event_id (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _result_id
     (setq _result_id (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _authkey
     (setq _authkey (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get motion::eventResult :md5sum-) "c7c4d92529537e5f02f61be920fd1adf")
(setf (get motion::eventResult :datatype-) "motion/eventResult")
(setf (get motion::eventResult :definition-)
      "int32 event_id
int32 result_id
int32 authkey

")



(provide :motion/eventResult "c7c4d92529537e5f02f61be920fd1adf")


