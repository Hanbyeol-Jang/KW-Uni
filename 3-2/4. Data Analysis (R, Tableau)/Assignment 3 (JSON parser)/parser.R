x<-c("twitteR","streamR","plyr","stringr")
install.packages(x)
lapply(x,require,character.only=TRUE)
parseTweets(fn)[,vnames]
parsj <- function(fn)
{vnames<-c("created_at","id_str","full_name","verified","text","source","in_reply_to_user_id_str","in_reply_to_screen_name","user_id_str","screen_name","followers_count","friends_count","listed_count","favourites_count","statuses_count","user_created_at",    "utc_offset","user_lang", "lang","geo_enabled", "lat","lon", "place_lat", "place_lon", "place_type","country_code")
tmp<-parseTweets(fn)[,vnames]
head(tmp)
length(tmp)
tmp$device <- substr(tmp$source, 1, nchar(tmp$source)-4)
tmp$device <- sub('.*\\">', "", tmp$device)
tmp$cdow  <- substr(tmp$created_at,1,3)
tmp$ucdow <- substr(tmp$user_created_at,1,3)
tmp$cdate <- paste(substr(tmp$created_at,27,30),"-",
                   substr(tmp$created_at,5,7),"-",
                   substr(tmp$created_at,9,10)," ",
                   substr(tmp$created_at,12,19),sep="")
tmp$ucdate <- paste(substr(tmp$user_created_at,27,30),"-",
                    substr(tmp$user_created_at,5,7),"-",
                    substr(tmp$user_created_at,9,10),sep="")
tmp$cdate <- gsub("Jan","01",tmp$cdate)
tmp$cdate <- gsub("Feb","02",tmp$cdate)
tmp$cdate <- gsub("Mar","03",tmp$cdate)
tmp$cdate <- gsub("Apr","04",tmp$cdate)
tmp$cdate <- gsub("May","05",tmp$cdate)
tmp$cdate <- gsub("Jun","06",tmp$cdate)
tmp$cdate <- gsub("Jul","07",tmp$cdate)
tmp$cdate <- gsub("Aug","08",tmp$cdate)
tmp$cdate <- gsub("Sep","09",tmp$cdate)
tmp$cdate <- gsub("Oct","10",tmp$cdate)
tmp$cdate <- gsub("Nov","11",tmp$cdate)
tmp$cdate <- gsub("Dec","12",tmp$cdate)
tmp$ucdate <- gsub("Jan","01",tmp$ucdate)
tmp$ucdate <- gsub("Feb","02",tmp$ucdate)
tmp$ucdate <- gsub("Mar","03",tmp$ucdate)
tmp$ucdate <- gsub("Apr","04",tmp$ucdate)
tmp$ucdate <- gsub("May","05",tmp$ucdate)
tmp$ucdate <- gsub("Jun","06",tmp$ucdate)
tmp$ucdate <- gsub("Jul","07",tmp$ucdate)
tmp$ucdate <- gsub("Aug","08",tmp$ucdate)
tmp$ucdate <- gsub("Sep","09",tmp$ucdate)
tmp$ucdate <- gsub("Oct","10",tmp$ucdate)
tmp$ucdate <- gsub("Nov","11",tmp$ucdate)
tmp$ucdate <- gsub("Dec","12",tmp$ucdate)
tmp$text=str_replace_all(tmp$text,"[[\r\n]]", "")
Encoding(tmp$device)<-"UTF-8"
tmp<-within(tmp, place_flag<-ifelse(!is.na(lon),"GPS","Cell"))
tmp<-within(tmp, lat<-ifelse(place_flag=="Cell",place_lat,lat))
tmp<-within(tmp, lon<-ifelse(place_flag=="Cell",place_lon,lon))
names(tmp)
tmp<-tmp[-c(1,6,28)]
names(tmp)
tmp
}

#######################################################
getwd()
fns <- list.files("/Users/Simon/Desktop/krkp", full.names=TRUE)
fns
length(fns)
fns<-fns[file.size(fns)>1024]
fnssub=tools::file_path_sans_ext(fns)
length(fns)
for (i in 1:length(fns)){
  fn <- paste(fns[1],"",sep="")
  cat("Parsing ", fn, "\n")
  tmp <- parsj(fn)
  fncsv <- paste("/Users/Simon/Desktop/output/",fnssub[i],".csv",sep="")
  cat("    Writing ", fncsv,"\n")
  write.csv(tmp,file=fncsv,row.names=F)
}



fns <- list.files("/Users/Simon/Desktop/sample", full.names=TRUE)
fns
length(fns)
fns<-fns[file.size(fns)>1024]
length(fns)
fnssub=substring(fns, 29)
for (i in 1:length(fns)){
  fn <- paste(fns[i],"",sep="")
  cat("Parsing ", fn, "\n")
  tmp <- parsj(fn)
  fncsv <- paste("/Users/Simon/Desktop/output/",fnssub[i],".csv",sep="")
  cat("    Writing ", fncsv,"\n")
  write.csv(tmp,file=fncsv,row.names=F)
}